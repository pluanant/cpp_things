# This is move semantics examples

Move semantics avoid the copy constructor which clone value to the new variable. On the other hand, move operation will "move" data to the new variable and handle the old variable to the proper state.

## Note:

- If you want to make existing variable to be temporary (rvalue), use std::move().
- If you want to move and assign, you should take care the existing data before move, otherwise memory leaks.
- Assign will be apply only if target variable already exist.
  - This call move operator
  ```c++
  String var_a = std::move(a);
  ```
  - This call moving assigned operator
  ```c++
  String var_a; var_a = std::move(a);
  ```

## More info:

- https://www.youtube.com/watch?v=ehMg6zvXuMY
- https://www.youtube.com/watch?v=OWNeCTd7yQE
