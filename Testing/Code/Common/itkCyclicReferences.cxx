/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit (ITK)
  Module:    itkCyclicReferences.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


Copyright (c) 2000 National Library of Medicine
All rights reserved.

See COPYRIGHT.txt for copyright details.

=========================================================================*/
#include <iostream>
#include "itkImage.h"
#include "itkScalar.h"
#include "itkVector.h"
#include "itkRandomImageSource.h"
#include "itkShrinkImage.h"
#include "itkWriteVTKImage.h"
#include "itkWriteRawImage.h"
#include "itkReadVTKImage.h"
#include "itkCommand.h"
#include "itkOutputWindow.h"


// this class is used to send output to stdout and not the itk window
class TextOutput : public itk::OutputWindow
{
public:
  virtual void DisplayText(const char* s)
    {
      std::cout << s << std::endl;
    }
};

// The following three classes are used to support callbacks
// on the shrink filter in the pipeline that follows later
class DeleteEvent
{
public:
  void Delete(itk::LightObject *caller, unsigned long event) 
    {std::cout << "Deleting: " << caller->GetClassName() << std::endl;}
};


int main()
{
  // Comment the following if you want to use the itk text output window
  itk::OutputWindow::SetInstance(new TextOutput);

  // Uncomment the following if you want to see each message independently
  // itk::OutputWindow::GetInstance()->PromptUserOn();

  // Test the creation of an image with native type
  //
  itk::Image<float,2>::Pointer if2 = itk::Image<float,2>::New();
  DeleteEvent deleteEvent;
  itk::MemberCommand<DeleteEvent>::Pointer deleteCommand;
  deleteCommand = itk::MemberCommand<DeleteEvent>::New();
  deleteCommand->SetCallbackFunction(&deleteEvent, &DeleteEvent::Delete);
  if2->AddObserver(itk::Command::DeleteEvent, deleteCommand);
  
  // Begin by creating a simple pipeline. Use the Scalar class as a pixel.
  //
  // Create a typedef to make the code more digestable
  typedef itk::Image<itk::Scalar<float>,2> FloatImage2DType;

  return EXIT_SUCCESS;
}



