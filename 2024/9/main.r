library(tidyverse)

t1 <- Sys.time()

task1 <- function(data) {
    for (i in 1:length(data)) {
        if (i > length(data)) { break }
        if (data[i] != -1) { next }

        n <- -1
        while (n == -1) {
            n <- data[length(data)]
            data <- data[-length(data)]
        }
        data[i] = n
    }

    return (data)
}

file_path <- "input.txt"
is_zero <- FALSE
index <- -1

data <- read_lines(file_path) %>% 
    str_split("") %>%
    unlist() %>% # Flatten the list
    map(~ as.integer(.x)) %>%
    map(~ {
        if (is_zero) {
            is_zero <<- FALSE
            rep(-1, .x)
        } else {
            is_zero <<- TRUE
            index <<- index + 1
            rep(index, .x)
        }
    }) %>%
    unlist() # Flatten


result <- task1(data) %>%
    { . * (seq_along(.)-1) } %>%
    sum()
    

print(paste(result))


t2 <- Sys.time()
duration <- (t2 - t1) * 1000
print(sprintf("Execution time: %.2f ms", duration))