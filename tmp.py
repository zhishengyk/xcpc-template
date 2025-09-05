def solution(paragraphs, aligns, width):
    res = []
    border = "*" * (width + 2)
    res.append(border)

    for words, align in zip(paragraphs, aligns):
        cur, cur_len = [], 0
        for w in words:
            if not cur:
                cur, cur_len = [w], len(w)
            elif cur_len + 1 + len(w) <= width:
                cur.append(w)
                cur_len += 1 + len(w)
            else:
                txt = " ".join(cur)
                pad = width - len(txt)
                if align == "LEFT":
                    res.append("*" + txt + " " * pad + "*")
                else:
                    res.append("*" + " " * pad + txt + "*")
                cur, cur_len = [w], len(w)

        if cur:
            txt = " ".join(cur)
            pad = width - len(txt)
            if align == "LEFT":
                res.append("*" + txt + " " * pad + "*")
            else:
                res.append("*" + " " * pad + txt + "*")

    res.append(border)
    return res