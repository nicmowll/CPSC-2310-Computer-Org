/*
 * Name: Nic Mowll
 * Username: nmowll
 * Lab4 004
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct NODE {
    int a;
    struct NODE *b;
    struct NODE *c;
};

struct NODE nodes[5] = {
    {5,	    nodes + 3, 	NULL},
	{15,	nodes + 4, 	nodes + 3},
	{22,	NULL,		nodes + 4},
	{12, 	nodes + 1, 	nodes},
	{18, 	nodes + 2, 	nodes + 1}
};

struct NODE *np = nodes + 2;
struct NODE **npp = &nodes[1].b;

int main() {
    printf("nodes\t%p\n", nodes);
    printf("nodes[3].a\t%i\n", nodes[3].a);
    printf("nodes[3].c\t%p\n", nodes[3].c);
    printf("nodes[3].c->a\t%i\n", nodes[3].c->a);
    printf("(*nodes).a\t%i\n", (*nodes).a);
    printf("nodes->a\t%i\n", nodes->a);
    printf("nodes[3].b->b\t%p\n", nodes[3].b->b);
    printf("&nodes\t%p\n", &nodes);
    printf("&nodes[3].a\t%p\n", &nodes[3].a);
    printf("&nodes[3].c\t%p\n", &nodes[3].c);
    printf("&nodes[3].c->a\t%p\n", &nodes[3].c->a);
    printf("&nodes->a\t%p\n", &nodes->a);
    printf("np\t%p\n", np);
    printf("np->a\t%i\n", np->a);
    printf("np->c->c->a\t%i\n", np->c->c->a);
    printf("npp\t%p\n", npp);
    printf("*npp\t%p\n", *npp);
    printf("(*npp)->a\t%i\n", (*npp)->a);
    printf("&np\t%p\n", &np);
    printf("&np->a\t%p\n", &np->a);
    printf("&np->c->c->a\t%p\n", &np->c->c->a);

    return 0;
}
