# tensorflow-qtcreator-cppApi
Run tensorflow using cpp_api on qtcreator to predict the score of image using tensorflow prebuilt binary on windows 10(64-bit)

# Description:
The program is used to load a tensorflow model (.pb) to predict the score of images in a folder
using tensorflow_cpp api.

# Pre-requisites:
1. Tensorflow Binary(Here 1.8 binary have been used):
Pre-built tensorflow binary can be downloaded from the following location:
https://github.com/fo40225/tensorflow-windows-wheel/tree/master/1.8.0/cpp.
<br>Note:
<br>Here i have used binary build using sse2 as i was finding linking issues in avx2 for my system
which i have to still verify.

2. Tensorflow Model (.pb):
Tensorflow model trained in python have used. The model was initially build using Keras and then converted into .pb
for using it in tensorflow.
<br>Note: 
<br>Note the input and output node of your model for giving input to the program

3. Opencv-Release files:
Link the opencv release lib files to the program.
The tensorflow lib is also built in release mode.

4. MSVC compiler:
Inorder to run the program we have to use MSVC compiler which have also been defined in the program.

5. Please refer the pro file for more details.

# Steps to Run the program:
Open the program in qt-creator. 
Give the path of image folder and tensorflow model. 
Build the program.
As this program is build in release mode include the necessary dll files in the release folder.
Note: Please copy paste all the necessary dll files required in the release folder during running the program

