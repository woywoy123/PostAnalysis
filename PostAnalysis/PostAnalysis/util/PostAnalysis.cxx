#include<PostAnalysis/BaseFunctionTest.h>
#include<PostAnalysis/Experimental.h>
#include<PostAnalysis/PresentationFigures.h>

int main(int argc, char** argv)
{
  int option = -1;

  // Run Tests 
  if (option == -1)
  {
    //PlotLandau(); 
    //PlotGaussian(); 
    //PlotGaussianXGaussian();
    //PlotLandauXLandau(); 
    //PlotLandauXGaussian(); 
    PlotDeconvGausXGaus(); 
    //PlotDeconvLandauXLandau(); // <--- needs fixing 
    //PlotDeconvLandauXGaussian(); 
    
  }

  // Produce Presentation Figures
  if (option == -2)
  {
    GaussianXGaussian(); 
    LandauXLandau(); 
  }

  // Run Experimental
  if (option == -3)
  {
  }
  
  
  
  std::cout << "fin" << std::endl;
  return 0; 

}
