loadI 1024 => r0
loadI 1 => r1
storeAI r1 => r0, 0
loadI 5 => r2
storeAI r2 => r0, 4
loadAI r0, 0 => r3
loadI 5 => r6
div r3, r6 => r7
storeAI r7 => r0, 8
loadI 6 => r8
loadI 4 => r9
div r8, r9 => r10
storeAI r10 => r0, 12
outputAI r0, 12
