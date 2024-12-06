# library(rlist)
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

repeat {
    pl = readLines(f, n = 1)
    if(identical(pl, "")){break} # If the line is empty, exit.
    # "12|34" -> matrix[12, 34] = 1
    matrix[as.numeric(substr(pl, 1, 2)),as.numeric(substr(pl, 4, 5))] <- 1
}

valid_page_total <- 0
invalid_page_total <- 0
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