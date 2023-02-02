# Smart Pointer

Wrapper around "pointer" which handle the heap allocation to avoid memory leaks. It depends on the type of smart pointer that is using so that the memory will be free on the different situation.

## Unique pointer

aka. scope pointer, after it out of scope, it will be destroy (call delete). This pointer type cannot copy.

## Shared pointer

You can share, copy this type of pointer, it will have count of how many pointer created, then if counter == 0, it will delete the memory allocation.

## Weak pointer 

It use with shared pointer but do not increase the pointer count so it will not keep the pointer alive. You can ask is the pointer expired or not.

## More info:

- https://www.youtube.com/watch?v=UOB7-B2MfwA&t
- https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170