library(tidyverse)

t1 <- Sys.time()



file_path <- "input.txt"
data <- read_lines(file_path)

print(results)

t2 <- Sys.time()
duration <- (t2 - t1) * 1000
print(sprintf("Execution time: %.2f ms", duration))