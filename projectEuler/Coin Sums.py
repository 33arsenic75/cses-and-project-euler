possible = [1, 2, 5, 10, 20, 50, 100, 200]
total_ways = [0] * 201  # Initialize the list with zeros
total_ways[0] = 1  # There's only one way to make zero

# Iterate over each coin denomination
for coin in possible:
    # Iterate over each amount from the value of the coin to 200
    for i in range(coin, 201):
        # Update the total ways by adding the ways to make (i - coin)
        total_ways[i] += total_ways[i - coin]

# Print the number of ways to make 200
print(total_ways[200])
