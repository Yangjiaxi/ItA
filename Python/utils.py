def close_ranger(left, right, step=None):
    if step is None:
        if left <= right:
            step = 1
        else:
            step = -1
    for idx in range(left, right + int(step / abs(step)), step):
        yield idx


if __name__ == "__main__":
    for po in [(1, 2, 2), (1, 1, 2), (10, -2, 3), (-10, 2, 3), (0, 0),
               (0, 5, -1), (2, -6, -2)]:
        print(po, list(close_ranger(*po)))
