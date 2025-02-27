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
#ifndef itkThinPlateR2LogRSplineKernelTransform_h
#define itkThinPlateR2LogRSplineKernelTransform_h

#include "itkKernelTransform.h"

namespace itk
{
/** \class ThinPlateR2LogRSplineKernelTransform
 * This class defines the thin plate spline (TPS) transformation.
 * It is implemented in as straightforward a manner as possible from
 * \cite davis1997.
 *
 * The kernel used in this variant of TPS is \f$ R^2 log(R) \f$
 *
 * \ingroup ITKTransform
 */
template <typename TParametersValueType, unsigned int VDimension = 3>
// Number of dimensions
class ITK_TEMPLATE_EXPORT ThinPlateR2LogRSplineKernelTransform
  : public KernelTransform<TParametersValueType, VDimension>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ThinPlateR2LogRSplineKernelTransform);

  /** Standard class type aliases. */
  using Self = ThinPlateR2LogRSplineKernelTransform;
  using Superclass = KernelTransform<TParametersValueType, VDimension>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** New macro for creation of through a Smart Pointer */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(ThinPlateR2LogRSplineKernelTransform);

  /** Scalar type. */
  using typename Superclass::ScalarType;

  /** Parameters type. */
  using typename Superclass::ParametersType;
  using typename Superclass::FixedParametersType;

  /** Jacobian Type */
  using typename Superclass::JacobianType;
  using typename Superclass::JacobianPositionType;
  using typename Superclass::InverseJacobianPositionType;

  /** Dimension of the domain space. */
  static constexpr unsigned int SpaceDimension = Superclass::SpaceDimension;

  using typename Superclass::InputPointType;
  using typename Superclass::OutputPointType;
  using typename Superclass::InputVectorType;
  using typename Superclass::OutputVectorType;
  using typename Superclass::InputCovariantVectorType;
  using typename Superclass::OutputCovariantVectorType;
  using typename Superclass::PointsIterator;

protected:
  ThinPlateR2LogRSplineKernelTransform() = default;
  ~ThinPlateR2LogRSplineKernelTransform() override = default;

  using typename Superclass::GMatrixType;
  /** Compute G(x)
   * For the thin plate spline, this is:
   * G(x) = r(x)*I
   * \f$ G(x) = r(x)^2 log(r(x) ) *I \f$
   * where
   * r(x) = Euclidean norm = sqrt[x1^2 + x2^2 + x3^2]
   * \f[ r(x) = \sqrt{ x_1^2 + x_2^2 + x_3^2 }  \f]
   * I = identity matrix. */
  void
  ComputeG(const InputVectorType & x, GMatrixType & gmatrix) const override;

  /** Compute the contribution of the landmarks weighted by the kernel function
      to the global deformation of the space  */
  void
  ComputeDeformationContribution(const InputPointType & thisPoint, OutputPointType & result) const override;
};
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkThinPlateR2LogRSplineKernelTransform.hxx"
#endif

#endif // itkThinPlateR2LogRSplineKernelTransform_h
