#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

// Structure to represent product prices
typedef struct
{
  int id;
  char name[128];
  double price;
  int quantity;
} prices_t;

// Function to count the number of columns in a comma-separated string
void count_columns(char *col_arr, int *countptr)
{
  char *token = strtok(col_arr, ",");
  
  // Iterate through tokens until NULL is encountered
  while (token != NULL)
  {
    ++(*countptr);  // Increment the count of columns
    token = strtok(NULL, ",");  // Move to the next token
  }
}

// Parse a comma-separated line and print each token
int parse_line(char *buffer)
{
  int ouput = 0;  // Counter for the number of tokens
  char *token = strtok(buffer, ",");

  // Iterate through tokens until NULL is encountered
  while (token != NULL)
  {
    ouput++;  // Increment the count of tokens
    printf("%-35s ", token);  // Print the token with left-aligned formatting
    token = strtok(NULL, ",");  // Move to the next token
  }

  printf("\n");

  return ouput;  // Return the total number of tokens
}

// Read product prices from a file
prices_t *read_prices(FILE *fp)
{
  prices_t *prices = calloc(1, sizeof(prices_t));  // Allocate memory for prices structure

  if (!prices)
  {
    return NULL;  // Return NULL if memory allocation fails
  }

  // Read values from the file into the prices structure
  fscanf(fp, "%d,%127[^,],%lf,%d", &prices->id, prices->name, &prices->price, &prices->quantity);

  return prices;  // Return the populated prices structure
}

// Print product prices
void print_prices(prices_t *p)
{
  printf("\nID\tNAME\t\tPRICE\tQTY\n");
  printf("\n%d\t%s\t\t%lf\t%d\n", p->id, p->name, p->price, p->quantity);
}

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  char col_arr[1000] = {0};
  int count = 0;
  prices_t prices;  // Declare prices structure variable

  if (argc != 2)
  {
    printf("USAGE: %s FILENAME\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];

  fp = fopen(filename, "r");

  if (fp == NULL)
  {
    perror("Could not open file");
    return 1;
  }

  fscanf(fp, "%[^\n]", col_arr);  // Read the header line of the file
  count_columns(col_arr, &count);  // Count the number of columns in the header

  printf("%-8s%-35s%-18s%-5s\n", "ID", "NAME", "PRICE", "QTY");  // Print formatted header

  if (count == 4)
  {
    // Read and print prices until the end of the file is reached
    while (fscanf(fp, "%d,%127[^,],%lf,%d", &prices.id, prices.name, &prices.price, &prices.quantity) == 4)
    {
      // Print each price with formatted columns
      printf("%-8d%-35s%-18.6lf%-5d\n", prices.id, prices.name, prices.price, prices.quantity);
    }
  }

  fclose(fp);  // Close the file

  return 0;
}
