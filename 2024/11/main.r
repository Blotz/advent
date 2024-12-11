library(tidyverse)

t1 <- Sys.time()

# use enviroment because it has O(1) access time
cache_env <- new.env()

count_rocks <- function(rock, n) {
    # base case
    if (n == 0) {
        return(1)
    }
    
    # cache
    key <- paste(rock, n, sep = "_")
    
    # cache hit
    if (exists(key, envir = cache_env)) {
        return(get(key, envir = cache_env))
    }
    
    # rule 1
    if (rock == 0) {
        result <- count_rocks(1, n - 1)
        assign(key, result, envir = cache_env)
        return(result)
    }
    
    # rule 2
    num_digits <- floor(log10(rock)) + 1
    if (num_digits %% 2 == 0) {
        d <- 10 ^ (num_digits / 2)
        a <- count_rocks(floor(rock / d), n - 1)
        b <- count_rocks(rock %% d, n - 1)
        result <- a + b
        assign(key, result, envir = cache_env)
        return(result)
    }
    
    # rule 3
    result <- count_rocks(rock * 2024, n - 1)
    assign(key, result, envir = cache_env)
    return(result)
}

file_path <- "input.txt"
numbers_list <- read_lines(file_path) %>%
  str_split(" ") %>%                    # Split the line by spaces
  map(as.integer) %>%                   # Convert to integers
  map(~ map(.x, ~count_rocks(.x, 75)))  # Process each number


# Print results
print(paste("Result:", sum(unlist(numbers_list))))

t2 <- Sys.time()
duration <- (t2 - t1) * 1000
print(sprintf("Execution time: %.2f ms", duration))