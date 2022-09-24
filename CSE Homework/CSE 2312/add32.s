.global addU32
.global addS32

.text

// uint32_t addU32(uint32_t x, uint32_t y)
// int32_t addS32(int32_t x, int32_t y)
// x in R0, y in R1, return result in R0
addU32:
addS32:
    ADD R0, R0, R1
    BX LR
