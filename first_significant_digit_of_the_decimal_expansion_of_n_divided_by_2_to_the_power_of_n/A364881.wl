(*For first 100k terms:*)
(*If you want to produce more or less, replace 100000 with the desired value.*)

Table[Floor[n/(2^n)/10^Floor[Log10[n/(2^n)]]], {n, 100000}]