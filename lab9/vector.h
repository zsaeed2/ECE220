typedef struct {
    int size;
    int maxSize;
    int * array;
} vector_t;

vector_t * createVector(int initialSize);
void destroyVector(vector_t * vector);
void resize(vector_t * vector);
void push_back(vector_t * vector, int element);
int pop_back(vector_t * vector);
int access(vector_t * vector, int index);
