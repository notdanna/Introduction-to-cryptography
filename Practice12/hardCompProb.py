def brute_force_discrete_log(base, mod, target):
    for x in range(mod):
        if pow(base, x, mod) == target:
            return x
    return None


cases = [
    ("a", 11, 1009, 400),
    ("b", 5, 10007, 5235),
    # ("c", 2, 100000000003, 1922556950),
    # ("d", 3, 500000009, 406870124),
    # ("e", 3, 500000009, 187776257),
]

for label, base, mod, target in cases:
    print(f"({label}) Resolving: {base}^x mod {mod} = {target}")
    x = brute_force_discrete_log(base, mod, target)

    if x is not None:
        print(f"({label}) Solution found: x = {x}\n")
    else:
        print(f"({label}) No solution found.\n")