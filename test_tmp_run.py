from tmp import solution


def run_tests():
    cases = [
        (
            [
                ["hello", "world"],
                ["how", "areyou", "doing"],
                ["please", "look", "and", "align", "to", "right"],
            ],
            ["LEFT", "RIGHT", "RIGHT"],
            16,
        ),
        (
            [
                ["x"],
                ["a", "b", "c", "d", "e"],
                ["long", "words"],
            ],
            ["RIGHT", "LEFT", "RIGHT"],
            5,
        ),
    ]

    for i, (pars, aligns, width) in enumerate(cases, 1):
        print(f"CASE {i}")
        out = solution(pars, aligns, width)
        for line in out:
            print(line)
        print()


if __name__ == "__main__":
    run_tests()





