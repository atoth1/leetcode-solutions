// https://leetcode.com/problems/sell-diminishing-valued-colored-balls/

const val modulus = 1000000007

class Solution {
    fun maxProfit(inventory: IntArray, orders: Int): Int {
        inventory.sortDescending()
        var numSold = 0
        var soldValue = 0
        for (id in 1..(inventory.size - 1)) {
            val diff = inventory[id - 1] - inventory[id]
            if (numSold.toLong() + id * diff >= orders.toLong()) {
                val numToSell = orders - numSold
                val numOfEach = numToSell / id
                val remainder = numToSell - id * numOfEach
                soldValue += ((id.toLong() * sumFromTo(inventory[id - 1] - numOfEach + 1,
                    inventory[id - 1])) % modulus).toInt()
                soldValue = soldValue % modulus
                soldValue += ((remainder.toLong() * (inventory[id - 1] - numOfEach)) % modulus).toInt()
                soldValue = soldValue % modulus
                numSold = orders
                break
            } else {
                numSold += id * diff
                soldValue += ((id.toLong() * sumFromTo(inventory[id] + 1, inventory[id - 1])) % modulus).toInt()
                soldValue = soldValue % modulus
            }
        }
        if (numSold < orders) {
            val numToSell = orders - numSold
            val numOfEach = numToSell / inventory.size
            val remainder = numToSell - inventory.size * numOfEach
            soldValue += ((inventory.size.toLong() * sumFromTo(inventory[inventory.size - 1] - numOfEach + 1,
                inventory[inventory.size - 1])) % modulus).toInt()
            soldValue = soldValue % modulus
            soldValue += ((remainder.toLong() * (inventory[inventory.size - 1] - numOfEach)) % modulus).toInt()
            soldValue = soldValue % modulus
            numSold = orders
        }
        return soldValue
    }
    
    private fun sumFromTo(from: Int, to: Int): Int {
        if (from > to) {
            return 0
        } else {
            val n = (to - from + 1).toLong()
            return (((n * (from + to)) / 2) % modulus).toInt()
        }
    }
}
