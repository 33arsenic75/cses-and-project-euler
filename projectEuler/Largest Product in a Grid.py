def storeValues(grid):
    gridStr = []
    with open("Largest Product in a Grid.txt") as f:
        lines = f.read().splitlines()

    for fila in lines:
        gridStr.append(fila.split())

    # Create a grid with ints
    for y in range(20):
        for x in range(20):
            grid[y][x] = int(gridStr[y][x])


def main():
    grid = [[0 for x in range(20)] for x in range(20)]
    storeValues(grid)

    products = []
    for x in range(20):
        for y in range(17):
            products.append(grid[y][x] * grid[y+1][x] * 
                grid[y+2][x] * grid[y+3][x])
    for y in range(20):
        for x in range(17):
            products.append(grid[y][x] * 
                grid[y][x+1] * grid[y][x+2] * grid[y][x+3])

    for y in range(17):
        for x in range(17):
            products.append(grid[y][x] * 
                grid[y+1][x+1] * grid[y+2][x+2] * grid[y+3][x+3])

    for y in range(17):
        for x in range(17):
            products.append(grid[y][x+3] * 
                grid[y+1][x+2] * grid[y+2][x+1] * grid[y+3][x])

    answer = max(products)
    print (answer)

if __name__ == "__main__":
    main()