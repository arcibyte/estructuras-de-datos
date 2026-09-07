def encontrar_flecha_mas_larga(cadena: str) -> int:
  
  max_longitud = -1

  # TODO: Implementar la lógica para buscar los tipos de flechas:
  # 1. izquierda simple: '<' seguido de cero o más '-'
  # 2. izquierda doble: '<' seguido de cero o más '='
  # 3. derecha simple: cero o más '-' seguido de '>'
  # 4. derecha doble: cero o más '=' seguido de '>'

  return max_longitud


def resolver() -> None:
  try:
    num_casos = int(input())
    for _ in range(num_casos):
      cadena = input().strip()
      resultado = encontrar_flecha_mas_larga(cadena)
      print(resultado)
  except (EOFError, ValueError):
    pass
  
#continuar

if __name__ == "__main__":
  resolver()