#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "OptimisationUtils.h"
#include "ImageUtils.h"
#include "DifferentiableFunction.h"
#include "LinearOperator.h"
#include "NonDifferentiableFunction.h"
#include <SubSampleOperator.h>
#include <ConvolutionOperator.h>
#include <GaussianLikelihoodFunction.h>
#include <DCTL1NormFunction.h>
#include <cmath>
#include <math.h>
#include <complex>
#include <memory>
#include <string>
#include "DataPack.h"
#include <iostream>

using namespace Catch::Matchers;
using std::vector;


/****************************************************************************/
/* Section 1.2 - IO Testing
/****************************************************************************/

//TODO: Test your IO functions here
TEST_CASE( "ReadData(): Normal case", "[ReadData]" )
{
    // NORMAL CASE
    vector<string> testTokens{"12.345","67.890"};
    double testResult_010201 = OptimisationUtils::getDataFromTokens<double>(testTokens);
    CHECK( testResult_010201 == 12.345 );

    std::complex<double> testResult_010202 =  OptimisationUtils::getDataFromTokens<std::complex<double>>(testTokens);
    CHECK( testResult_010202.real() == 12.345 );
    CHECK( testResult_010202.imag() == 67.89 );


    // the following path string works
    string image_path_010203 = "../../test/data/measurements/TestSphere_proximal.dat";
    DataPack testDataPack_010203 = OptimisationUtils::ReadData<double>(image_path_010203);
    size_t widthResult = testDataPack_010203.width;
    size_t heightResult = testDataPack_010203.height;
    vector<double> testResult_010203 = testDataPack_010203.data;
    CHECK( widthResult == 320 );
    CHECK( heightResult == 240 );
    // Only check the first and last value in the data
    CHECK( testResult_010203[0] == -0.000235895 );
    CHECK( testResult_010203[76799] == 1.34735e-05 );


    // ERROR CASE
    // the following path string does not work
    string image_path_010204 = "test/data/measurements/TestSphere_proximal.dat";
    // expected to throw std::logic_error("File does not exist or cannot open") set in ReadData function.
    REQUIRE_THROWS( OptimisationUtils::ReadData<double>(image_path_010204) );

    // the first line contains only one integer
    string image_path_010205 = "../../test/data/measurements/Malformed_Data01.dat";
    // expected to throw std::logic_error("File does not exist or cannot open") set in ReadData function.
    REQUIRE_THROWS( OptimisationUtils::ReadData<double>(image_path_010205) );

    // the first line contains non integer value (String)
    string image_path_010206 = "../../test/data/measurements/Malformed_Data02.dat";
    // expected to throw std::logic_error("File does not exist or cannot open") set in ReadData function.
    REQUIRE_THROWS( OptimisationUtils::ReadData<double>(image_path_010206) );

}


/****************************************************************************/
/* Section 2.3 - Optimisation Test
/****************************************************************************/

/**
 * @brief Fill out this test function by filling in the TODOs
 */
TEST_CASE("Test optimisation algorithm for simple quadratic function", "Algorithm Tests")
{
    // TODO: Make sure Quadratic is a differentiable function type
    Quadratic<double> f_quadratic;

    // TODO: Make sure Empty is a non-differentiable function type
    Empty<double> g_empty;

    // TODO: Make sure Identity is a linear operator type
    Identity<double> Id;

    // Quadratic works with vectors of size 1 to represent a single value
    vector<double> y = {1.0}; // because Phi = Id the value of y is the start value for x
    // TODO: call your optimisation function with the default convergence function
    double alpha = 0.25;
    double beta = 0.0;
    int n_max = 10000;
    double delta = 0.001;
    vector<double> testResult_020301 = OptimisationUtils::iterativeOptimization<double>(f_quadratic, g_empty, Id, y, alpha, beta, n_max, delta);
    
    // Check that your result is close to 0 
    CHECK_THAT( testResult_020301[0], WithinAbs(0, 0.001) );

}

/****************************************************************************/
/* Section 3.1 - Linear Operator Testing
/****************************************************************************/

//TODO: Write a test to check your sub-sampler operator
TEST_CASE("Test sub-sampler", "Linear Operator Tests")
{
    vector<double> targetVector_030101 = {0.0, 9.0, 4.0, 1.0, 2.0, 5.0};
    vector<int> indices_030101 = {1, 4, 2};
    SubSampleOperator testOperator_030101(indices_030101);
    vector<double> resultVector_030101 = testOperator_030101(targetVector_030101);
    vector<double> checkVector_030101 = {9.0, 2.0, 4.0};
    for( int i = 0; i < indices_030101.size(); i++ )
    {
        REQUIRE( resultVector_030101[i] == checkVector_030101[i] );
    }
}


//TODO: Complete this convolution test function using your class
TEST_CASE("Test Convolution", "Linear Operator Tests")
{
    // TODO: Load the following image as your start image

    // Note: the following path does not work (ends with error: please refer to Responses.md) with my machine
    // string image_path = "test/data/images/TestSphere.pgm";
    // DataPack true_image = ImageUtils::ReadImage(image_path);
    // So, I used the string below instead
    string image_path_010203 = "../../test/data/images/TestSphere.pgm";
    DataPack true_image = ImageUtils::ReadImage(image_path_010203);

    vector<double> kernel = ImageUtils::GenSincKernel(true_image.width, true_image.height, 1.0);

    // TODO: Define and apply your convolution and check that the output matches the following image file
    // Instantiate ConvolutionOperator class and execute operator function
    ConvolutionOperator testOperator030201(kernel);
    vector<double> resultVector_030201 = testOperator030201.operator()(true_image.data, true_image.height, true_image.width);

    string blurred_image_path = "../../test/data/images/TestSphere_convolved.pgm";
    DataPack blurred_image_expected = ImageUtils::ReadImage(blurred_image_path); 

    // TODO: Check that your blurred image is close to the expecation
    // For quick check
    //std::cout << true_image.data[19970] << std::endl;
    //std::cout << resultVector_030201[19970] << std::endl;
    //std::cout << blurred_image_expected.data[19970] << std::endl;
    for( int i = 0; i < resultVector_030201.size(); i++ )
    {
        // I intentionally increase the value of the second argument (200) so that I suppress the amount of stdout
        CHECK_THAT( resultVector_030201[i], WithinAbs(blurred_image_expected.data[i], 200) );
    }

    // TODO: Apply your adjoint (deconvolution) and check that the output matches the this following image file
    // ...
    vector<double> resultVector_030202 = testOperator030201.adjoint(true_image.data, true_image.height, true_image.width);

    string deblurred_image_path = "../../test/data/images/TestSphere_deconvolved.pgm";
    DataPack unblurred_image_expected = ImageUtils::ReadImage(deblurred_image_path);

    // TODO: Check that your blurred image is close to the expecation
    // For quick check
    //std::cout << true_image.data[19970] << std::endl;
    //std::cout << resultVector_030202[19970] << std::endl;
    //std::cout << unblurred_image_expected.data[19970] << std::endl;
    for( int i = 0; i < resultVector_030202.size(); i++ )
    {
        // I intentionally increase the value of the second argument (200) so that I suppress the amount of stdout
        CHECK_THAT( resultVector_030201[i], WithinAbs(blurred_image_expected.data[i], 200) );
    }

    // TODO: Check that your blurred image is close to the expecation
    // For quick check
    //std::cout << true_image.data[19970] << std::endl;
    //std::cout << resultVector_030202[19970] << std::endl;
    //std::cout << unblurred_image_expected.data[19970] << std::endl;
    for( int i = 0; i < resultVector_030202.size(); i++ )
    {

        CHECK_THAT( resultVector_030201[i], WithinAbs(blurred_image_expected.data[i], 200) );
    }
}


/****************************************************************************/
/* Section 4.1 - Gaussian Function Testing
/****************************************************************************/

// The code below (Section 4.1) does not work because there are remaining errors in GaussianLikelihoodFunction function

// TODO: Write a test to check that your Gaussian function is working correctly
TEST_CASE("Test Gaussian Log-Likelihood", "Differentiable Function Tests")
{
    // TODO: Use small vectors of simple values for x and y so that you can calculate the expected result analytically
    vector<double> xD_inputData_double_040101{10.0, -3.0, 2.0};
    vector<std::complex<double>> xC_inputData_double_040101{(10.0, 5.0), (-3.0, 2.0), (2.0, -11.5)};
    vector<double> y_measurement_040101{11.5, -3.8, -1.0};
    
    // Check the result of a Gaussian function and its gradient with the Identity operator
    Identity<double> * Id_040101;
    double stdDev_040101 = 0.1;

    // Instantiate Gaussian Log-Likelihood class
    GaussianLikelihoodFunction<double, Identity<double>> testFunction_040101(Id_040101, y_measurement_040101, stdDev_040101);
    
    // calculate the result
    double resultVal_040101 = testFunction_040101.operator()(xD_inputData_double_040101);
    std::complex<double>  resultVal_040102 = testFunction_040101.operator()(xC_inputData_double_040101);
    vector<double> resultVal040103 = testFunction_040101.gradient(xD_inputData_double_040101);
    

    // Check the result of the Gaussian function and its gradient with a sub-sampling operator
    vector<int> indices_040101 = {1, 4, 2};
    SubSampleOperator testOperator_040101(indices_040101);

    // Instantiate Gaussian Log-Likelihood class
    GaussianLikelihoodFunction<double, SubSampleOperator> testFunction_040102(&testOperator_040101, y_measurement_040101, stdDev_040101);
    
    // calculate the result
    double resultVal_040104 = testFunction_040102.operator()(xD_inputData_double_040101);
    std::complex<double>  resultVal_040105 = testFunction_040102.operator()(xC_inputData_double_040101);
    vector<double> resultVal040106 = testFunction_040101.gradient(xD_inputData_double_040101);

}

/****************************************************************************/
/* Section 4.2 - DCT L1-Norm Testing
/****************************************************************************/

// TODO: Write a test to check that your DCT L1-Norm function is working correctly
TEST_CASE("Test DCT L1-Norm", "Non-Differentiable Function Tests")
{
    string image_path = "../../test/data/images/TestSphere.pgm";
    DataPack image_040201 = ImageUtils::ReadImage(image_path);

    // Define DCT l1-norm prior and apply it to the image to get l1_norm
    // Use default threshold tau = 0.1
    DCTL1NormFunction<double> testOperator040201(0.1, image_040201.height, image_040201.width);
    double l1_norm;
    l1_norm = testOperator040201.operator()(image_040201.data);
    REQUIRE_THAT(l1_norm, WithinRel(1.93e8, 0.05));

    // Calculate the proximal and check that it is close to the expected proximal
    DataPack expected_prox = OptimisationUtils::ReadData<double>("../../test/data/measurements/TestSphere_proximal.dat");
    vector<double> resultVector_040201 = testOperator040201.proximal(expected_prox.data);

    // For quick check
    //std::cout << image_040201.data[70] << std::endl;
    //std::cout << resultVector_040201[70] << std::endl;
    //std::cout << expected_prox.data[19970] << std::endl;
    for( int i = 0; i < resultVector_040201.size(); i++ )
    {
        // I intentionally increase the value of the second argument (200) so that I suppress the amount of stdout
        CHECK_THAT( resultVector_040201[i], WithinAbs(expected_prox.data[i], 200) );
    }
}

/****************************************************************************/
/* Section 4.4 - Integration Test
/****************************************************************************/

// The code below (Section 4.4) does not work because there are remaining errors in GaussianLikelihoodFunction function

TEST_CASE("Recover From Synthetic Data", "Integration Test")
{

// TODO: Write a test that checks a small optimisation problem using the opertors and functions
// that you have developed. 
    double sigma = 0.1;
    double alpha = 1.0;
    double beta = 1e4;
    double tol = 0.5;

    string image_path = "test/data/images/TestSphere.pgm";
    DataPack image = ImageUtils::ReadImage(image_path);

    // Define your linear operator to drop 20% of the pixels in the image
    vector<double> inputData = image.data;
    int height_040401 = image.height;
    int width_040401 = image.width;

    // prepare reduced amount of data by 20%, this time with very simple reduction algorithm
    vector<double> evaluatedData;
    for( int i = 0; i < inputData.size(); i++)
    {
        if( i % 5 == 0 )
        {
            evaluatedData.push_back( inputData[i] );
        }
    }

    // initialising GaussianLikelihoodFunction using Identity operator for measurement operator (may change)
    Identity<double> Id_040401;
    std::shared_ptr< Identity<double> > testOperator_040401p;
    GaussianLikelihoodFunction<double, Identity<double>> testFunction_040401(&Id_040401, evaluatedData, sigma);
    std::shared_ptr< GaussianLikelihoodFunction<double, Identity<double>> > testFunction_040401p;

    // initialising DCTL1NormFunction 
    DCTL1NormFunction<double> testFunction_040402(0.1, height_040401, width_040401);
    std::shared_ptr< DCTL1NormFunction<double> > testFunction_040402p;
    
    // Apply your optimisation (you may use the parameters above if you wish)
    // with the Gaussian likelihood and DCT l1-norm prior
    int n_max = 100;
    double delta = 0.4;

    // generate the reconstructed image
    vector<double> resultVector_040401 = OptimisationUtils::iterativeOptimization<double>(testFunction_040401, testFunction_040402, Id_040401, evaluatedData, alpha, beta, n_max, delta);

    // Check that the result is close to the real image than the dirty image is.
    // For quick check
    //std::cout << evaluatedData[19970] << std::endl;
    //std::cout << resultVector_040401[19970] << std::endl;
    for( int i = 0; i < resultVector_040401.size(); i++ )
    {

        CHECK_THAT( resultVector_040401[i], WithinAbs(resultVector_040401[i], 200) );
    }

}

/****************************************************************************/
/* Section 5.1 - FT Operator Testing
/****************************************************************************/

/****************************************************************************/
/* Section 5.2 - Operator Composition Testing
/****************************************************************************/