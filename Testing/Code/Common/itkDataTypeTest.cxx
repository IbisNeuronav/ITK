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
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include <iostream>
#include "itkVector.h"



int itkDataTypeTest(int, char* [] )
{
  int status = 0;
  itk::Vector<int, 4> v;

  v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
  std::cout << "Vector value = ";
  for (unsigned int i=0; i < v.GetVectorDimension(); i++)
    {
    if (v[i] != static_cast<int>(i + 1))
      {
      std::cout << std::endl << "ERROR: v[" << i << "] = " << v[i] << " but should = " << i + 1 << std::endl;
      status++;
      }
    std::cout << v[i];
    if (i < v.GetVectorDimension() - 1)
      {
      std::cout << ", ";
      }
    }
  std::cout << std::endl;

  return status;
}
