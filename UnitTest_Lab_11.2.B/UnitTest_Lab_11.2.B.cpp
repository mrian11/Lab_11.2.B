#include "pch.h"
#include "CppUnitTest.h"
#include "../Project4/Source.cpp" // Adjust the path based on your project structure

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab112B
{
    TEST_CLASS(UnitTestLab112B)
    {
    public:

        TEST_METHOD(TestPhysicsGrade5Students)
        {
           
            std::string testFileName = "testfile.bin"; 
            std::ofstream testFile(testFileName, std::ios_base::binary);

            Student std_Ph5;
            strcpy_s(std_Ph5.Prizv, "TestStudent");
            std_Ph5.Phisic = 5;

            Student std_oth;
            strcpy_s(std_oth.Prizv, "OtherStudent");
            std_oth.Phisic = 4;

            testFile.write(reinterpret_cast<const char*>(&std_Ph5), sizeof(Student));
            testFile.write(reinterpret_cast<const char*>(&std_oth), sizeof(Student));

            testFile.close();

            PhysicsGrade5Students(testFileName);

            remove(testFileName.c_str()); 
        }
    };
}
