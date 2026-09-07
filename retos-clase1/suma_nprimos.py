def criba_eratostenes(n: int) -> list[bool]:
  #implementacion de un arreglo booleano indicando que nuemros son primos hasta n.
  es_primo = [True] * (n + 1)
  es_primo[0] = es_primo[1] = False
  for i in range(2, int(n**0.5) + 1):
    if es_primo[i]:
      for j in range(i * i, n + 1, i):
        es_primo[j] = False
  return es_primo


def resolver() -> None:
  limite_maximo = 10000
  es_primo = criba_eratostenes(limite_maximo)
  primos = [i for i, p in enumerate(es_primo) if p]

  try:
    num_casos = int(input())

    for _ in range(num_casos):
      p = int(input())

      encontrado = False
      for a in primos:
        if a > p:
          break
        for b in primos:
          if b < a:
            continue
          if a + b > p:
            break
          c = p - a - b
          if c < b:
            break
          if c <= limite_maximo and es_primo[c]:
            print(f"{a} {b} {c}")
            encontrado = True
            break
        if encontrado:
          break
  except (EOFError, ValueError):
    pass


if __name__ == "__main__":
  resolver()