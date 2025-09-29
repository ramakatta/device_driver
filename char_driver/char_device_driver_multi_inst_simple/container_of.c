#include <stdio.h>
#include <stddef.h> // Required for offsetof

#define container_of(ptr, type, member) ({ \
    (type *)( (char *)(ptr) - offsetof(type, member) ); \
})


struct student {
    char name[20];
    int roll_no;
    int course_code;
    int marks;
};

int main() {
    struct student stu;
    int *pMarks = &stu.marks; // Pointer to `marks`
    
    // Get the address of `stu` using `pMarks`
    struct student *pStu = container_of(pMarks, struct student, marks);
    
    if (pStu == &stu) {
        printf("Successfully retrieved struct address using container_of!\n");
    }
}
