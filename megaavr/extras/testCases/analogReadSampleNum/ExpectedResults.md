# Expected Results for this Test Case

Actual numbers may vary depending on the voltage input, however this is based off of the original results from our original 
sample program: https://github.com/jnbrauer/SER401-2022-Group39-Documentation/tree/main/ADC/ADC_diff_modes  

Result with 1 samples accumulated: 944  
Result with 4 samples accumulated: 3774  
Result with 16 samples accumulated: 15097  
Result with 64 samples accumulated: 60382  
Result with 190 samples accumulated: 944  

This last result should return to a default of 1 sample since 190 is not an expected value.  
Anything with a result that exceeds 65535 will behave unexpectedly since that is larger than the results register can store.
