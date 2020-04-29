/*
 * This file contains the definitions of structures you'll use for this
 * assignment along with prototypes of functions you'll have to write.  You
 * should not modify anything in this file.
 */

#include "dynarray.h"

/*
 * This structure represents information about a single product from the store.
 */
struct product {
	char* name;
	int inventory;
	float price;
};


/*
 * These are the prototypes of the functions you will write in products.c.
 * See the documentation in products.c for more information about each
 * function.
 */
struct product* create_product(char* name, int inventory, float price);
void free_product(struct product* product);
struct dynarray* create_product_array(int num_products, char** names, int* inventories, float* prices);
void free_product_array(struct dynarray* products);
void print_products(struct dynarray* products);
struct product* find_max_price(struct dynarray* products);
struct product* find_max_investment(struct dynarray* products);
void sort_by_inventory(struct dynarray* products);
