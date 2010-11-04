/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkSampleClassifierFilter_txx
#define __itkSampleClassifierFilter_txx

#include "itkSampleClassifierFilter.h"

namespace itk
{
namespace Statistics
{
template< class TSample >
SampleClassifierFilter< TSample >
::SampleClassifierFilter()
{
  this->m_NumberOfClasses = 0;

  this->SetNumberOfRequiredInputs(3);
  this->SetNumberOfRequiredOutputs(1);

  this->ProcessObject::SetNthOutput( 0, this->MakeOutput(0) );

  /** Initialize decision rule */
  m_DecisionRule = NULL;
}

template< class TSample >
void
SampleClassifierFilter< TSample >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "NumberofClasses: "
     << this->GetNumberOfClasses() << std::endl;
  os << indent << "DecisionRule: "
     << this->GetDecisionRule() << std::endl;
}

template< class TSample >
void
SampleClassifierFilter< TSample >
::SetInput(const TSample *sample)
{
  // Process object is not const-correct so the const_cast is required here
  this->ProcessObject::SetNthInput( 0,
                                    const_cast< SampleType * >( sample ) );
}

template< class TSample >
const TSample *
SampleClassifierFilter< TSample >
::GetInput() const
{
  if ( this->GetNumberOfInputs() < 1 )
    {
    return 0;
    }

  return static_cast< const SampleType * >
         ( this->ProcessObject::GetInput(0) );
}

template< class TSample >
void
SampleClassifierFilter< TSample >
::SetClassLabels(const ClassLabelVectorObjectType *classLabels)
{
  // Process object is not const-correct so the const_cast is required here
  this->ProcessObject::SetNthInput( 1,
                                    const_cast< ClassLabelVectorObjectType * >( classLabels ) );
}

template< class TSample >
void
SampleClassifierFilter< TSample >
::SetMembershipFunctions(const MembershipFunctionVectorObjectType *membershipFunctions)
{
  // Process object is not const-correct so the const_cast is required here
  this->ProcessObject::SetNthInput( 2,
                                    const_cast< MembershipFunctionVectorObjectType * >( membershipFunctions ) );
}

template< class TSample >
void
SampleClassifierFilter< TSample >
::SetMembershipFunctionsWeightsArray(const
                                     MembershipFunctionsWeightsArrayObjectType *weightsArray)
{
  // Process object is not const-correct so the const_cast is required here
  this->ProcessObject::SetNthInput( 3,
                                    const_cast<
                                      MembershipFunctionsWeightsArrayObjectType * >( weightsArray ) );
}

template< class TSample >
typename SampleClassifierFilter< TSample >::DataObjectPointer
SampleClassifierFilter< TSample >
::MakeOutput(unsigned int)
{
  return static_cast< DataObject * >( MembershipSampleType::New().GetPointer() );
}

template< class TSample >
void
SampleClassifierFilter< TSample >
::GenerateData()
{
  const ClassLabelVectorObjectType *classLabelsDecorated =
    static_cast< const ClassLabelVectorObjectType * >( this->ProcessObject::GetInput(1) );

  const MembershipFunctionVectorObjectType *membershipFunctionsDecorated =
    static_cast< const MembershipFunctionVectorObjectType * >( this->ProcessObject::GetInput(2) );

  const MembershipFunctionsWeightsArrayObjectType *
  membershipFunctionsWeightsArrayDecorated =
    static_cast< const MembershipFunctionsWeightsArrayObjectType * >( this->ProcessObject::GetInput(3) );

  const ClassLabelVectorType & classLabels = classLabelsDecorated->Get();

  const MembershipFunctionVectorType & membershipFunctions = membershipFunctionsDecorated->Get();

  // Check number of Labels and MembershipSamples against the number of classes
  // */
  if ( membershipFunctions.size() != this->m_NumberOfClasses )
    {
    itkExceptionMacro("Number of Membership functions does not match the number of classes");
    }

  if ( classLabels.size() != this->m_NumberOfClasses )
    {
    itkExceptionMacro("Number of class labels does not match the number of classes");
    }

  if ( m_DecisionRule.IsNull() )
    {
    itkExceptionMacro("Decision rule is not set");
    }

  MembershipFunctionsWeightsArrayType membershipFunctionsWeightsArray;
  if ( membershipFunctionsWeightsArrayDecorated == NULL )
    {
    // no weights array is set and hence all membership functions will have
    // equal
    // weight
    membershipFunctionsWeightsArray.SetSize(this->m_NumberOfClasses);
    membershipFunctionsWeightsArray.Fill(1.0);
    }
  else
    {
    membershipFunctionsWeightsArray = membershipFunctionsWeightsArrayDecorated->Get();
    }

  if ( membershipFunctionsWeightsArray.Size() != this->m_NumberOfClasses
       )
    {
    itkExceptionMacro(
      "Membership functions weight array size does not match the\
                      number of classes "                                                                  );
    }

  const SampleType *sample =
    static_cast< const SampleType * >( this->ProcessObject::GetInput(0) );

  std::vector< double > discriminantScores;
  discriminantScores.resize(this->m_NumberOfClasses);

  MembershipSampleType *output = dynamic_cast< MembershipSampleType * >(
    this->ProcessObject::GetOutput(0) );

  output->SetSample( this->GetInput() );
  output->SetNumberOfClasses(this->m_NumberOfClasses);

  typename TSample::ConstIterator iter = sample->Begin();
  typename TSample::ConstIterator end  = sample->End();

  while ( iter != end )
    {
    typename TSample::MeasurementVectorType measurements;
    measurements = iter.GetMeasurementVector();
    for ( unsigned int i = 0; i < this->m_NumberOfClasses; i++ )
      {
      discriminantScores[i] = membershipFunctionsWeightsArray[i]
                              * membershipFunctions[i]->Evaluate(measurements);
      }

    unsigned int classIndex;
    classIndex = m_DecisionRule->Evaluate(discriminantScores);

    output->AddInstance( classLabels[classIndex], iter.GetInstanceIdentifier() );
    ++iter;
    }
}

template< class TSample >
const typename SampleClassifierFilter< TSample >::MembershipSampleType *
SampleClassifierFilter< TSample >
::GetOutput() const
{
  return static_cast< const MembershipSampleType * >( this->ProcessObject::GetOutput(0) );
}
} // end of namespace Statistics
} // end of namespace itk

#endif
