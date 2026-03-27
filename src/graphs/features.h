#pragma once
#include "TownsCountries.h"
#include "minHeap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printCountryTowns(Country** arrWithCountries, int quantity);
bool areThereAnyTownsLeft(Town** allTowns, int quantityOftowns);
void algorithm(Country** allCountries, Town** allTowns, int quantityOfCountries, int quantityOftowns);
