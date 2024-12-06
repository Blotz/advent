# the matrix contains the relationship between pages.
# which(matrix[12,]!=0) returns all the pages that 12 comes before.
# likewise, which(matrix[,34]!=0) returns all the pages that come before 34
# 
# using the come-before relatonship, we can check if a page appears before a page that it shouldnt.
# page <- 12
# required pages <- (34, 56, 78)
# if any of the required pages appear after page 12, then the page ordering is invalid
# 
# you can quickly fix the ordering using a bubble sort like algorithm
# for each page, check if any of the required pages appear after the page
# if they do, move the violating page to just before the current page
# repeat until the ordering is valid
# Eventually, the ordering will be valid kinda like a bubble sort
# 
# bubble sort is O(n^2) which is better than the O(n!) brute force approach


start <- Sys.time()

is_valid <- function(matrix, pages) {
    for (i in seq_along(pages)) {
        current_page <- pages[i]
        
        # Find pages that need to come before the current page
        required_pages <- which(matrix[, current_page] != 0)
        
        # Check if any of those pages appear in the list of pages after the current page
        if (any(required_pages %in% pages[i:length(pages)])) {
            return(FALSE)
        }
    }
    return(TRUE)
}

fix_ordering <- function(matrix, pages) {
    while (!is_valid(matrix, pages)) {
        for (i in seq_along(pages)) {
            current_page <- pages[i]
            required_pages <- which(matrix[, current_page] != 0)
            
            # Check for violations and fix them
            for (p in required_pages) {
                if (p %in% pages[(i + 1):length(pages)]) {
                    # Move the violating page to the correct position
                    pages <- pages[pages != p] # Remove the violating page
                    pages <- append(pages, p, after = i - 1) # Insert it before the current page
                }
            }
        }
    }
    
    return(pages)
}

# define 100x100 matrix
matrix <- matrix(0, nrow = 99, ncol = 99)

f = file("input.txt", "r")

# this will read each line until it reaches an empty line
# all the lines before the empty line will be used to populate the matrix
repeat {
    pl = readLines(f, n = 1)
    if(identical(pl, "")){break} # If the line is empty, exit.
    # "12|34" -> matrix[12, 34] = 1
    matrix[as.numeric(substr(pl, 1, 2)),as.numeric(substr(pl, 4, 5))] <- 1
}

valid_page_total <- 0
invalid_page_total <- 0
# this continues reading the lines from where the previous loop left off
# each line is a list of pages
repeat {
    pl = readLines(f, n = 1)
    if(identical(pl, character(0))){break} # If the line is empty, exit.
    # "75,47,61,53,29" -> (75, 47, 61, 53, 29)
    int_vector <- as.integer(unlist(strsplit(pl, ",")))
    if (is_valid(matrix, int_vector)) {
        # get middle value
        valid_page_total <- valid_page_total + int_vector[ceiling(length(int_vector)/2)]
    } else {
        # fix invalid page
        int_vector <- fix_ordering(matrix, int_vector)
        invalid_page_total <- invalid_page_total + int_vector[ceiling(length(int_vector)/2)]
    }
}

print(valid_page_total)
print(invalid_page_total)
Sys.time()-start