library(tidyverse)
library(purrr) # pmap

t1 <- Sys.time()

is_in_bounds <- function(matrix, x, y) {
    return (x >= 1 && x <= nrow(matrix) && y >= 1 && y <= ncol(matrix))
}

directions <- list(
    c(-1, 0),  # Up
    c(1, 0),   # Down
    c(0, -1),  # Left
    c(0, 1)    # Right
)

follow_trail <- function(matrix, x, y) {
    current_value <- matrix[x, y]

    # Base case
    if (current_value == 9) {
        return (1)
    }

    count <- 0
    for (direction in directions) {
        new_x <- x + direction[1]
        new_y <- y + direction[2]

        if (is_in_bounds(matrix, new_x, new_y) && matrix[new_x, new_y] == current_value + 1) {
            count <- count + follow_trail(matrix, new_x, new_y)
        }
    }
    return (count)
}

file_path <- "input.txt"
matrix <- read_lines(file_path) %>%
    map(~ # process each row
        str_split(.x, "") %>%     # Split the line by characters
        map(~ as.integer(.x)) %>% # Convert to integers
        unlist()                  # Flatten back to a vector
    ) %>%
    do.call(rbind, .) # Bind rows into a matrix

results <- which(matrix == 0, arr.ind = TRUE) %>%
    # call follow_trail(matrix, x, y) each indices returned by which
    as.data.frame() %>%
    pmap(~ follow_trail(matrix, ..1, ..2)) %>%
    unlist() %>%
    sum()

print(results)

t2 <- Sys.time()
duration <- (t2 - t1) * 1000
print(sprintf("Execution time: %.2f ms", duration))