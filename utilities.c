#include <stdio.h>
#include <stdlib.h>
#include "double_ended_list.h"
#include "self_sorting_list.h"
#include "tree.h"
#include "utilities.h"

void emergencyExit () {
	treeDeleteTree(errorTree);
}