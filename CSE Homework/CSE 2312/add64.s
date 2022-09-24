.global addU64

.text

// uint64_t addU64(uint64_t x, uint64_t y)
// x in R1:R0, y in R3:R2, return result in R1:R0
addU64:
    ADDS R0, R0, R2 // C:R0 <- R0 + R2
    ADC  R1, R1, R3 // R1 <- R1 + R3 + C
    BX LR // go back to caller
