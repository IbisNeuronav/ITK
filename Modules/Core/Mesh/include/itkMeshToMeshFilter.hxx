/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
/*=========================================================================
 *
 *  Portions of this file are subject to the VTK Toolkit Version 3 copyright.
 *
 *  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 *
 *  For complete copyright, license and disclaimer of warranty information
 *  please refer to the NOTICE file at the top of the ITK source tree.
 *
 *=========================================================================*/
#ifndef itkMeshToMeshFilter_hxx
#define itkMeshToMeshFilter_hxx

#include "itkMesh.h"

namespace itk
{

template <typename TInputMesh, typename TOutputMesh>
MeshToMeshFilter<TInputMesh, TOutputMesh>::MeshToMeshFilter()
{
  // Modify superclass default values, can be overridden by subclasses
  this->SetNumberOfRequiredInputs(1);
}

template <typename TInputMesh, typename TOutputMesh>
void
MeshToMeshFilter<TInputMesh, TOutputMesh>::SetInput(const TInputMesh * input)
{
  // Process object is not const-correct so the const_cast is required here
  this->ProcessObject::SetNthInput(0, const_cast<TInputMesh *>(input));
}

template <typename TInputMesh, typename TOutputMesh>
auto
MeshToMeshFilter<TInputMesh, TOutputMesh>::GetInput() const -> const InputMeshType *
{
  return itkDynamicCastInDebugMode<const TInputMesh *>(this->GetPrimaryInput());
}

template <typename TInputMesh, typename TOutputMesh>
auto
MeshToMeshFilter<TInputMesh, TOutputMesh>::GetInput(unsigned int idx) const -> const InputMeshType *
{
  return dynamic_cast<const TInputMesh *>(this->ProcessObject::GetInput(idx));
}

template <typename TInputMesh, typename TOutputMesh>
void
MeshToMeshFilter<TInputMesh, TOutputMesh>::CopyInputMeshToOutputMeshPoints()
{
  const InputMeshType *   inputMesh = this->GetInput();
  const OutputMeshPointer outputMesh = this->GetOutput();

  using OutputPointsContainer = typename TOutputMesh::PointsContainer;
  using InputPointsContainer = typename TInputMesh::PointsContainer;

  auto                         outputPoints = OutputPointsContainer::New();
  const InputPointsContainer * inputPoints = inputMesh->GetPoints();

  if (inputPoints)
  {
    outputPoints->Reserve(inputPoints->Size());

    typename InputPointsContainer::ConstIterator       inputItr = inputPoints->Begin();
    const typename InputPointsContainer::ConstIterator inputEnd = inputPoints->End();

    typename OutputPointsContainer::Iterator outputItr = outputPoints->Begin();

    while (inputItr != inputEnd)
    {
      outputItr.Value() = inputItr.Value();
      ++inputItr;
      ++outputItr;
    }

    outputMesh->SetPoints(outputPoints);
  }
}

template <typename TInputMesh, typename TOutputMesh>
void
MeshToMeshFilter<TInputMesh, TOutputMesh>::CopyInputMeshToOutputMeshPointData()
{
  const InputMeshType *   inputMesh = this->GetInput();
  const OutputMeshPointer outputMesh = this->GetOutput();

  using OutputPointDataContainer = typename TOutputMesh::PointDataContainer;
  using InputPointDataContainer = typename TInputMesh::PointDataContainer;

  auto                            outputPointData = OutputPointDataContainer::New();
  const InputPointDataContainer * inputPointData = inputMesh->GetPointData();

  if (inputPointData)
  {
    outputPointData->Reserve(inputPointData->Size());

    typename InputPointDataContainer::ConstIterator       inputItr = inputPointData->Begin();
    const typename InputPointDataContainer::ConstIterator inputEnd = inputPointData->End();

    typename OutputPointDataContainer::Iterator outputItr = outputPointData->Begin();

    while (inputItr != inputEnd)
    {
      outputItr.Value() = inputItr.Value();
      ++inputItr;
      ++outputItr;
    }

    outputMesh->SetPointData(outputPointData);
  }
}

template <typename TInputMesh, typename TOutputMesh>
void
MeshToMeshFilter<TInputMesh, TOutputMesh>::CopyInputMeshToOutputMeshCellLinks()
{
  const InputMeshType *   inputMesh = this->GetInput();
  const OutputMeshPointer outputMesh = this->GetOutput();

  using OutputCellLinksContainer = typename TOutputMesh::CellLinksContainer;
  using InputCellLinksContainer = typename TInputMesh::CellLinksContainer;

  auto                            outputCellLinks = OutputCellLinksContainer::New();
  const InputCellLinksContainer * inputCellLinks = inputMesh->GetCellLinks();

  if (inputCellLinks)
  {
    outputCellLinks->Reserve(inputCellLinks->Size());

    typename InputCellLinksContainer::ConstIterator       inputItr = inputCellLinks->Begin();
    const typename InputCellLinksContainer::ConstIterator inputEnd = inputCellLinks->End();

    typename OutputCellLinksContainer::Iterator outputItr = outputCellLinks->Begin();

    while (inputItr != inputEnd)
    {
      outputItr.Value() = inputItr.Value();
      ++inputItr;
      ++outputItr;
    }

    outputMesh->SetCellLinks(outputCellLinks);
  }
}

template <typename TInputMesh, typename TOutputMesh>
void
MeshToMeshFilter<TInputMesh, TOutputMesh>::CopyInputMeshToOutputMeshCells()
{
  const InputMeshType *   inputMesh = this->GetInput();
  const OutputMeshPointer outputMesh = this->GetOutput();

  using OutputCellsContainer = typename TOutputMesh::CellsContainer;
  using InputCellsContainer = typename TInputMesh::CellsContainer;
  using CellAutoPointer = typename TOutputMesh::CellAutoPointer;

  outputMesh->SetCellsAllocationMethod(MeshEnums::MeshClassCellsAllocationMethod::CellsAllocatedDynamicallyCellByCell);

  auto                        outputCells = OutputCellsContainer::New();
  const InputCellsContainer * inputCells = inputMesh->GetCells();

  if (inputCells)
  {
    outputCells->Reserve(inputCells->Size());

    typename InputCellsContainer::ConstIterator       inputItr = inputCells->Begin();
    const typename InputCellsContainer::ConstIterator inputEnd = inputCells->End();

    typename OutputCellsContainer::Iterator outputItr = outputCells->Begin();

    CellAutoPointer clone;

    while (inputItr != inputEnd)
    {
      //      outputItr.Value() = inputItr.Value();
      // BUG: FIXME: Here we are copying a pointer, which is a mistake. What we
      // should do is to clone the cell.
      inputItr.Value()->MakeCopy(clone);
      outputItr.Value() = clone.ReleaseOwnership();

      ++inputItr;
      ++outputItr;
    }

    outputMesh->SetCells(outputCells);
  }
}

template <typename TInputMesh, typename TOutputMesh>
void
MeshToMeshFilter<TInputMesh, TOutputMesh>::CopyInputMeshToOutputMeshCellData()
{
  const InputMeshType *   inputMesh = this->GetInput();
  const OutputMeshPointer outputMesh = this->GetOutput();

  using OutputCellDataContainer = typename TOutputMesh::CellDataContainer;
  using InputCellDataContainer = typename TInputMesh::CellDataContainer;

  auto                           outputCellData = OutputCellDataContainer::New();
  const InputCellDataContainer * inputCellData = inputMesh->GetCellData();

  if (inputCellData)
  {
    outputCellData->Reserve(inputCellData->Size());

    typename InputCellDataContainer::ConstIterator       inputItr = inputCellData->Begin();
    const typename InputCellDataContainer::ConstIterator inputEnd = inputCellData->End();

    typename OutputCellDataContainer::Iterator outputItr = outputCellData->Begin();

    while (inputItr != inputEnd)
    {
      outputItr.Value() = inputItr.Value();
      ++inputItr;
      ++outputItr;
    }

    outputMesh->SetCellData(outputCellData);
  }
}
} // end namespace itk

#endif
