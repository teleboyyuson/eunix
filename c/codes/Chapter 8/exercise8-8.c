#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NALLOC 1024  // minimum units to request

typedef long Align; // for alignment to long boundary

union header {
    struct {
        union header *next;
        unsigned size;
    } s;
    Align x; // force alignment
};

typedef union header Header;

static Header base;          // empty list to get started
static Header *freep = NULL; // start of free list

// malloc_custom: general-purpose storage allocator
void *malloc_custom(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {
        base.s.next = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.next; ; prevp = p, p = p->s.next) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits) {
                prevp->s.next = p->s.next;
            } else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) {
            return NULL; // no block found
        }
    }
}

// free_custom: put block ap in free list
void free_custom(void *ap) {
    if (ap == NULL) return;

    Header *bp = (Header *)ap - 1;
    Header *p;

    for (p = freep; !(bp > p && bp < p->s.next); p = p->s.next) {
        if (p >= p->s.next && (bp > p || bp < p->s.next)) {
            break;
        }
    }

    if (bp + bp->s.size == p->s.next) {
        bp->s.size += p->s.next->s.size;
        bp->s.next = p->s.next->s.next;
    } else {
        bp->s.next = p->s.next;
    }

    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.next = bp->s.next;
    } else {
        p->s.next = bp;
    }

    freep = p;
}

// bfree: add arbitrary block to free list
void bfree(void *p, unsigned n) {
    printf("bfree() called with ptr = %p, size = %u\n", p, n);

    if (n < sizeof(Header)) {
        fprintf(stderr, "bfree error: size too small\n");
        return;
    }

    if ((uintptr_t)p % sizeof(Header) != 0) {
        fprintf(stderr, "bfree error: pointer not aligned to %zu bytes\n", sizeof(Header));
        return;
    }

    // 🔥 Ensure the free list is initialized
    if (freep == NULL) {
        base.s.next = freep = &base;
        base.s.size = 0;
    }

    Header *bp = (Header *)p;
    bp->s.size = n / sizeof(Header);
    printf("Adding block to free list. Units: %u\n", bp->s.size);

    free_custom((void *)(bp + 1));
}


int main() {
    static Align static_buffer[128]; // 128 * sizeof(long), aligned

    printf("Adding static buffer to free list...\n");
    bfree(static_buffer, sizeof(static_buffer));

    printf("Allocating 100 bytes using malloc_custom...\n");
    int *x = (int *)malloc_custom(100);
    if (x == NULL) {
        printf("malloc_custom failed\n");
        return 1;
    }

    for (int i = 0; i < 25; i++) {
        x[i] = i * 2;
        printf("x[%d] = %d\n", i, x[i]);
    }

    printf("Freeing the allocated memory...\n");
    free_custom(x);

    printf("Done.\n");
    return 0;
}

