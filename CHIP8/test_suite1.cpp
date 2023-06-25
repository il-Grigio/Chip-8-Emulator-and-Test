//file test_suite1.c
#define CLOVE_SUITE_NAME MySuite01
#include "clove-unit.h"
#include "Chippotto.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>


CLOVE_SUITE_SETUP_ONCE() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        }
    }
}

CLOVE_TEST(JP_Test)
{
    chipotto::Emulator EmulatorInit;
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode1(0x1300));
    CLOVE_INT_EQ((int)0x0300 - 2, (int)EmulatorInit.GetPC());
}

CLOVE_TEST(CALL_Test)
{
    chipotto::Emulator EmulatorInit;
    for (uint8_t i = 0; i <= (int)0xF ; i++)
    {
        CLOVE_INT_EQ((int)chipotto::OpcodeStatus::NotIncrementPC, (int)EmulatorInit.Opcode2(0x2300));
        CLOVE_INT_EQ(i, (int)EmulatorInit.GetSP());
        CLOVE_INT_EQ((int)0x0300, (int)EmulatorInit.GetPC());

    }
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::StackOverflow, (int)EmulatorInit.Opcode2(0x2300));
    CLOVE_INT_EQ(0xF, (int)EmulatorInit.GetSP());
}

CLOVE_TEST(SE_Test) {
    chipotto::Emulator EmulatorInit;
    uint16_t my_PC = (int)EmulatorInit.GetPC();
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode3(0x3300));
    CLOVE_INT_EQ(my_PC + 2, (int)EmulatorInit.GetPC());

    my_PC = (int)EmulatorInit.GetPC();
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode3(0x3401));
    CLOVE_INT_EQ(my_PC, (int)EmulatorInit.GetPC());
}

CLOVE_TEST(SNE_Test) {
    chipotto::Emulator EmulatorInit;
    uint16_t my_PC = (int)EmulatorInit.GetPC();
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode4(0x4300));
    CLOVE_INT_EQ(my_PC, (int)EmulatorInit.GetPC());

    my_PC = (int)EmulatorInit.GetPC();
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode4(0x4401));
    CLOVE_INT_EQ(my_PC + 2, (int)EmulatorInit.GetPC());
}

CLOVE_TEST(SE_XY_Test) {
    chipotto::Emulator EmulatorInit;
    uint16_t my_PC = (int)EmulatorInit.GetPC();
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode5(0x5300));
    CLOVE_INT_EQ(my_PC + 2, (int)EmulatorInit.GetPC());

    my_PC = (int)EmulatorInit.GetPC();
    EmulatorInit.Opcode6(0x6788);
    EmulatorInit.Opcode6(0x6899);
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode5(0x5780));
    CLOVE_INT_EQ(my_PC, (int)EmulatorInit.GetPC());
    
}

CLOVE_TEST(LD_Test) {
    chipotto::Emulator EmulatorInit;
    uint16_t my_PC = (int)EmulatorInit.GetPC();
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode6(0x6345));
    EmulatorInit.Opcode3(0x3345);
    CLOVE_INT_EQ(my_PC + 2, (int)EmulatorInit.GetPC());

    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode6(0x6456));
    my_PC = (int)EmulatorInit.GetPC();
    EmulatorInit.Opcode4(0x4445);
    CLOVE_INT_EQ(my_PC + 2, (int)EmulatorInit.GetPC());
}

CLOVE_TEST(ADD_Test) {
    chipotto::Emulator EmulatorInit;
    uint16_t my_PC = (int)EmulatorInit.GetPC();

    EmulatorInit.Opcode6(0x6101);
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode7(0x7123));
    EmulatorInit.Opcode3(0x3124);
    CLOVE_INT_EQ(my_PC + 2, (int)EmulatorInit.GetPC());

}

CLOVE_TEST(SNE_XY_Test) {
    chipotto::Emulator EmulatorInit;
    uint16_t MyPc = (int)EmulatorInit.GetPC();
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode9(0x9780));
    CLOVE_INT_EQ(MyPc, (int)EmulatorInit.GetPC());

    EmulatorInit.Opcode6(0x6702);
    EmulatorInit.Opcode6(0x6805);
    MyPc = (int)EmulatorInit.GetPC();
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode9(0x9780));
    CLOVE_INT_EQ(MyPc + 2, (int)EmulatorInit.GetPC());
}

CLOVE_TEST(LD_I_Test) {
    chipotto::Emulator EmulatorInit;
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.OpcodeA(0xA001));
    CLOVE_INT_EQ((int)0x1, (int)EmulatorInit.GetI());
}

CLOVE_TEST(JP_V0_Test) {
    chipotto::Emulator EmulatorInit;
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.OpcodeB(0xB300));
    CLOVE_INT_EQ((int)0x0300 - 2, (int)EmulatorInit.GetPC());

    EmulatorInit.Opcode6(0x6012);
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.OpcodeB(0xB400));
    CLOVE_INT_EQ((int)0x0412 - 2, (int)EmulatorInit.GetPC());
}

CLOVE_TEST(LD_XY_Test)
{
    chipotto::Emulator EmulatorInit;
    EmulatorInit.Opcode6(0x6456); //Y Register[4] = 0x56
    EmulatorInit.Opcode6(0x6304); //X Register[3] = 0x4
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8340));
    CLOVE_INT_EQ(0x56, (int)EmulatorInit.GetRegister(3));
}

CLOVE_TEST(OR_XY_Test)
{
    chipotto::Emulator EmulatorInit;
    EmulatorInit.Opcode6(0x6456); //Y Register[4] = 0x56
    EmulatorInit.Opcode6(0x6308); //X Register[3] = 0x8
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8341));
    CLOVE_INT_EQ(0x5E, (int)EmulatorInit.GetRegister(3));
}

CLOVE_TEST(AND_XY_Test)
{
    chipotto::Emulator EmulatorInit;
    EmulatorInit.Opcode6(0x6456); //Y Register[4] = 0x56
    EmulatorInit.Opcode6(0x630C); //X Register[3] = 0xC
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8342));
    CLOVE_INT_EQ(0x4, (int)EmulatorInit.GetRegister(3));
}

CLOVE_TEST(XOR_XY_Test)
{
    chipotto::Emulator EmulatorInit;
    EmulatorInit.Opcode6(0x6456); //Y Register[4] = 0x56
    EmulatorInit.Opcode6(0x630C); //X Register[3] = 0xC
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8343));
    CLOVE_INT_EQ(0x5A, (int)EmulatorInit.GetRegister(3));
}

CLOVE_TEST(ADD_XY_Test)
{
    chipotto::Emulator EmulatorInit;
    EmulatorInit.Opcode6(0x6456); //Y Register[4] = 0x56
    EmulatorInit.Opcode6(0x630C); //X Register[3] = 0xC
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8344));
    CLOVE_INT_EQ(0x62, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x0, (int)EmulatorInit.GetRegister(0xF));
    
    
    EmulatorInit.Opcode6(0x64FF); //Y Register[4] = 0xFF
    EmulatorInit.Opcode6(0x630C); //X Register[3] = 0xC
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8344));
    CLOVE_INT_EQ(0x0B, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x1, (int)EmulatorInit.GetRegister(0xF));
}

CLOVE_TEST(SUB_XY_Test)
{
    chipotto::Emulator EmulatorInit;
    EmulatorInit.Opcode6(0x6456); //Y Register[4] = 0x56
    EmulatorInit.Opcode6(0x630C); //X Register[3] = 0xC
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8345));
    CLOVE_INT_EQ(0x100 - 0x4A, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x0, (int)EmulatorInit.GetRegister(0xF));
    
    
    EmulatorInit.Opcode6(0x640C); //Y Register[4] = 0xC
    EmulatorInit.Opcode6(0x6356); //X Register[3] = 0x56
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8345));
    CLOVE_INT_EQ(0x4A, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x1, (int)EmulatorInit.GetRegister(0xF));
}

CLOVE_TEST(SHR_XY_Test)
{
    chipotto::Emulator EmulatorInit;
    EmulatorInit.Opcode6(0x6456); //Y Register[4] = 0x56
    
    EmulatorInit.Opcode6(0x630C); //X Register[3] = 0xC
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8346));
    CLOVE_INT_EQ(0x6, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x0, (int)EmulatorInit.GetRegister(0xF));
    
    
    EmulatorInit.Opcode6(0x630D); //X Register[3] = 0x56
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8346));
    CLOVE_INT_EQ(0x6, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x1, (int)EmulatorInit.GetRegister(0xF));
}

CLOVE_TEST(SUBN_XY_Test)
{
    chipotto::Emulator EmulatorInit;
    EmulatorInit.Opcode6(0x6456); //Y Register[4] = 0x56
    EmulatorInit.Opcode6(0x630C); //X Register[3] = 0xC
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8347));
    CLOVE_INT_EQ(0x4A, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x1, (int)EmulatorInit.GetRegister(0xF));
    
    
    EmulatorInit.Opcode6(0x640C); //Y Register[4] = 0xC
    EmulatorInit.Opcode6(0x6356); //X Register[3] = 0x56
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x8347));
    CLOVE_INT_EQ(0x100 - 0x4A, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x0, (int)EmulatorInit.GetRegister(0xF));
}

CLOVE_TEST(SHL_XY_Test)
{
    chipotto::Emulator EmulatorInit;
    EmulatorInit.Opcode6(0x6456); //Y Register[4] = 0x56

    EmulatorInit.Opcode6(0x630C); //X Register[3] = 0xC
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x834E));
    CLOVE_INT_EQ(0x18, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x0, (int)EmulatorInit.GetRegister(0xF));


    EmulatorInit.Opcode6(0x63F4); //X Register[3] = 0xF4
    CLOVE_INT_EQ((int)chipotto::OpcodeStatus::IncrementPC, (int)EmulatorInit.Opcode8(0x834E));
    CLOVE_INT_EQ(0xE8, (int)EmulatorInit.GetRegister(3));
    CLOVE_INT_EQ(0x1, (int)EmulatorInit.GetRegister(0xF));
}

//CLOVE_SUITE_TEARDOWN()
//{
//    delete Emulator;
//}
//CLOVE_SUITE_TEARDOWN_ONCE()
//{
//    delete Emulator;
//    SDL_Quit();
//}