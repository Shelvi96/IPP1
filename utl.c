#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"
#include "utl.h"

void emergencyExit () {
	treeDeleteTree(errorTree);
}