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
// this file defines the itkCommonTest for the test driver
// and all it expects is that you have a function called RegisterTests
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif
#include <iostream>
#include "itkTestMain.h"


void RegisterTests()
{
REGISTER_TEST(itkBSplineDeformableTransformTest2 );
REGISTER_TEST(itkBSplineDeformableTransformTest3 );
REGISTER_TEST(itkCellInterfaceTest);
REGISTER_TEST(itkImageTransformTest);
REGISTER_TEST(itkLinearInterpolateImageFunctionTest);
REGISTER_TEST(itkMaximumDecisionRuleTest );
REGISTER_TEST(itkMaximumRatioDecisionRuleTest );
REGISTER_TEST(itkNonUniformBSplineTest );
REGISTER_TEST(itkDifferenceImageFilterTest );
REGISTER_TEST(itkImageToImageFilterTest );
REGISTER_TEST(itkMeanImageFunctionTest );
REGISTER_TEST(itkMedialNodeCorrespondencesTest );
REGISTER_TEST(itkMedianImageFunctionTest );
REGISTER_TEST(itkMemoryLeakTest );
REGISTER_TEST(itkMeshTest );
REGISTER_TEST(itkMeshFstreamTest );
REGISTER_TEST(itkMeshSourceGraftOutputTest );
REGISTER_TEST(itkMetaDataDictionaryTest );
REGISTER_TEST(itkMinimumDecisionRuleTest );
REGISTER_TEST(itkMultiThreaderTest );
REGISTER_TEST(itkNearestNeighborExtrapolateImageFunctionTest );
REGISTER_TEST(itkNeighborhoodTest );
REGISTER_TEST(itkNeighborhoodIteratorTest );
REGISTER_TEST(itkNeighborhoodOperatorImageFunctionTest);
REGISTER_TEST(itkNeighborhoodOperatorTest );
REGISTER_TEST(itkNumericTraitsTest );
REGISTER_TEST(itkIntTypesTest);
REGISTER_TEST(itkObjectStoreTest );
REGISTER_TEST(itkObjectFactoryTest );
REGISTER_TEST(itkObjectFactoryTest2 );
REGISTER_TEST(itkOctreeTest );
REGISTER_TEST(itkOrthogonallyCorrected2DParametricPathTest );
REGISTER_TEST(itkOrientedImage3DTest );
REGISTER_TEST(itkOrientedImage2DTest );
REGISTER_TEST(itkOrientedImageProfileTest1 );
REGISTER_TEST(itkOrientedImageProfileTest2 );
REGISTER_TEST(itkOrientedImageProfileTest3 );
REGISTER_TEST(itkPathFunctionsTest );
REGISTER_TEST(itkPathIteratorTest );
REGISTER_TEST(itkPCAShapeSignedDistanceFunctionTest );
REGISTER_TEST(itkPeriodicBoundaryConditionTest );
REGISTER_TEST(itkPhasedArray3DSpecialCoordinatesImageTest );
REGISTER_TEST(itkPixelAccessTest );
REGISTER_TEST(itkPointGeometryTest );
REGISTER_TEST(itkPointSetTest );
REGISTER_TEST(itkPolyLineParametricPathTest );
REGISTER_TEST(itkPolygonCellTest );
REGISTER_TEST(itkQuaternionRigidTransformTest );
REGISTER_TEST(itkRealTimeClockTest );
REGISTER_TEST(itkRGBPixelTest );
REGISTER_TEST(itkRGBInterpolateImageFunctionTest );
REGISTER_TEST(itkRGBToVectorImageAdaptorTest );
REGISTER_TEST(itkRigid2DTransformTest );
REGISTER_TEST(itkRigid3DTransformTest );
REGISTER_TEST(itkRigid3DPerspectiveTransformTest );
REGISTER_TEST(itkScalarToRGBPixelFunctorTest );
REGISTER_TEST(itkScatterMatrixImageFunctionTest );
REGISTER_TEST(itkScaleSkewVersor3DTransformTest );
REGISTER_TEST(itkScaleVersor3DTransformTest );
REGISTER_TEST(itkScaleTransformTest );
REGISTER_TEST(itkScaleLogarithmicTransformTest );
REGISTER_TEST(itkSemaphoreTest );
REGISTER_TEST(itkShapedNeighborhoodIteratorTest );
REGISTER_TEST(itkSimilarity2DTransformTest );
REGISTER_TEST(itkSimilarity3DTransformTest );
REGISTER_TEST(itkSimpleFilterWatcherTest );
REGISTER_TEST(itkSimplexMeshTest );
REGISTER_TEST(itkSizeTest );
REGISTER_TEST(itkSliceIteratorTest );
REGISTER_TEST(itkSmartPointerTest );
REGISTER_TEST(itkSparseImageTest );
REGISTER_TEST(itkSpatialFunctionTest );
REGISTER_TEST(itkSphereSignedDistanceFunctionTest );
REGISTER_TEST(itkSplineKernelTransformTest );
REGISTER_TEST(itkSTLContainerAdaptorTest );
REGISTER_TEST(itkStdStreamLogOutputTest );
REGISTER_TEST(itkThreadDefsTest );
REGISTER_TEST(itkThreadLoggerTest );
REGISTER_TEST(itkTimeProbesTest );
REGISTER_TEST(itkTimeStampTest );
REGISTER_TEST(itkTransformTest );
REGISTER_TEST(itkTransformFactoryBaseTest );
REGISTER_TEST(itkTransformsSetParametersTest );
REGISTER_TEST(itkTranslationTransformTest );
REGISTER_TEST(itkTreeContainerTest );
REGISTER_TEST(itkTreeContainerTest2 );
REGISTER_TEST(itkTriangleCellTest );
REGISTER_TEST(itkVarianceImageFunctionTest );
REGISTER_TEST(itkVectorGeometryTest );
REGISTER_TEST(itkVectorImageTest );
REGISTER_TEST(itkVectorMeanImageFunctionTest );
REGISTER_TEST(itkVersorTransformTest );
REGISTER_TEST(itkVersorTest );
REGISTER_TEST(itkVersorRigid3DTransformTest );
REGISTER_TEST(itkVectorTest );
REGISTER_TEST(itkVectorInterpolateImageFunctionTest );
REGISTER_TEST(itkVectorToRGBImageAdaptorTest );
REGISTER_TEST(itkMathRoundTest );
REGISTER_TEST(itkMathRoundTest2 );
REGISTER_TEST(itkVNLRoundProfileTest1 );
REGISTER_TEST(itkMathRoundProfileTest1 );
REGISTER_TEST(itkMathCastWithRangeCheckTest );
REGISTER_TEST(itkWindowedSincInterpolateImageFunctionTest );
REGISTER_TEST(itkEllipsoidInteriorExteriorSpatialFunctionTest );
REGISTER_TEST(itkSymmetricEllipsoidInteriorExteriorSpatialFunctionTest );
REGISTER_TEST(itkSymmetricSecondRankTensorTest );
REGISTER_TEST(itkSymmetricEigenAnalysisTest );
REGISTER_TEST(itkZeroFluxBoundaryConditionTest );
//This is a separate executable REGISTER_TEST(itkSystemInformationTest );
REGISTER_TEST(itkSTLThreadTest );
REGISTER_TEST(itkVariableLengthVectorTest);
REGISTER_TEST(itkVariableSizeMatrixTest);
// REGISTER_TEST(itkQuaternionOrientationAdapterTest);
REGISTER_TEST(itkImportContainerTest);
REGISTER_TEST(itkImageFillBufferTest);

// QuadEdge - Pure Topology Layer
REGISTER_TEST(itkQuadEdgeTest1);
// Geometrical Quad Edge - topology and geometry
REGISTER_TEST(itkQuadEdgeMeshNoPointConstTest);
REGISTER_TEST(itkGeometricalQuadEdgeTest1);
// QuadEdgeMesh - the complete structure
REGISTER_TEST(itkQuadEdgeMeshPointTest1);
REGISTER_TEST(itkQuadEdgeMeshAddFaceTest1);
REGISTER_TEST(itkQuadEdgeMeshAddFaceTest2);
REGISTER_TEST(itkQuadEdgeMeshBasicLayerTest);
REGISTER_TEST(itkQuadEdgeMeshDeleteEdgeTest);
REGISTER_TEST(itkQuadEdgeMeshFrontIteratorTest);
REGISTER_TEST(itkQuadEdgeMeshIteratorTest);
REGISTER_TEST(itkQuadEdgeMeshPointTest1);
REGISTER_TEST(itkQuadEdgeMeshTest1);
REGISTER_TEST(itkQuadEdgeMeshTest2);
REGISTER_TEST(itkQuadEdgeMeshTest3);
REGISTER_TEST(itkQuadEdgeMeshPolygonCellTest);
REGISTER_TEST(itkQuadEdgeMeshCellInterfaceTest);
REGISTER_TEST(itkQuadEdgeMeshCountingCellsTest);
REGISTER_TEST(itkQuadEdgeMeshDeletePointAndReorderIDsTest);
REGISTER_TEST(itkDynamicQuadEdgeMeshTest);
// QuadEdgeMesh - Euler Operators
REGISTER_TEST(itkQuadEdgeMeshEulerOperatorCreateCenterVertexTest);
REGISTER_TEST(itkQuadEdgeMeshEulerOperatorDeleteCenterVertexTest);
REGISTER_TEST(itkQuadEdgeMeshEulerOperatorFlipTest);
REGISTER_TEST(itkQuadEdgeMeshEulerOperatorJoinFacetTest);
REGISTER_TEST(itkQuadEdgeMeshEulerOperatorJoinVertexTest);
REGISTER_TEST(itkQuadEdgeMeshEulerOperatorSplitEdgeTest);
REGISTER_TEST(itkQuadEdgeMeshEulerOperatorSplitFaceTest);
REGISTER_TEST(itkQuadEdgeMeshEulerOperatorSplitVertexTest);
// QuadEdgeMEsh helpers
REGISTER_TEST(itkTriangleHelperTest);
REGISTER_TEST(itkCrossHelperTest);
REGISTER_TEST(itkPriorityQueueTest);
REGISTER_TEST(itkPriorityQueueTest);
REGISTER_TEST(itkFloatingPointExceptionsTest);
}
