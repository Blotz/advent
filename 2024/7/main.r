library(tidyverse)
library(stringr)
library(gtools)

data <- data.frame("one"= readLines("input.txt"))

start <- Sys.time()

df <- data %>%
  separate(one, into = c("result", "using"), sep = ": ")

df$result <- as.numeric(df$result)
df$match <- FALSE
# using_lists <- str_split(df$using, " ")
# convert to ints
using_lists <- str_split(df$using, " ") %>% map(~as.numeric(.x))

max_length <- max(sapply(using_lists, length))
# count df$using rows

find_sum <- function(result, numbers) {
    n1 <- numbers[1]
    n2 <- numbers[2]
    numbers <- numbers[-c(1, 2)]

    add <- n1 + n2
    mult <- n1 * n2

    if (length(numbers) == 0) {
        return (result == add | result == mult)
    }

    if (add < result) { if (find_sum(result, c(add, numbers))) { return (TRUE)} }
    if (mult < result) { if (find_sum(result, c(mult, numbers))) { return (TRUE)} }

    return (FALSE)
}
total <- 0
for(i in 1:nrow(df)){
    if (find_sum(df$result[i], using_lists[[i]])) {
        total <- total + df$result[i]
    }
}

print(paste("result", total))

Sys.time()-start