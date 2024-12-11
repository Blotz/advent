library(tidyverse)
library(stringr)  # str_strip

start <- Sys.time()

is_valid <- function(result, numbers) {
    n1 <- numbers[1]
    n2 <- numbers[2]
    numbers <- numbers[-c(1, 2)]

    add <- n1 + n2
    mult <- n1 * n2

    if (length(numbers) == 0) {
        return (result == add | result == mult)
    }

    if (add < result) { 
        if (is_valid(result, c(add, numbers))) {
            return (TRUE)
        }
    }
    if (mult < result) { 
        if (is_valid(result, c(mult, numbers))) { 
            return (TRUE)
        } 
    }

    return (FALSE)
}

file_path <- "input.txt"
result <- read_lines(file_path) %>%
    str_split(":") %>%
    map(~ {
        target <- .x[1] %>%
            as.numeric()  # target exceeds integer range
        numbers <- .x[2] %>%
            str_trim() %>%
            str_split(" ") %>%
            map(~ as.numeric(.x)) %>%  # numbers excced integer range
            unlist()

        ifelse(is_valid(target, numbers), target, 0)
    }) 


print(paste("result", sum(unlist(result))))

Sys.time()-start