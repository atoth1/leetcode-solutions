// https://leetcode.com/problems/design-a-food-rating-system/

import java.util.TreeSet

class FoodRatings(foods: Array<String>, cuisines: Array<String>, ratings: IntArray) {
    
    private data class CuisineData(val food: String, val rating: Int)
    
    private val foodToCuisine = mutableMapOf<String, String>()
    private val foodToRating = mutableMapOf<String, Int>()
    private val cuisineLookup = mutableMapOf<String, TreeSet<CuisineData>>()
    
    init {
        for (id in 0 until foods.size) {
            foodToCuisine[foods[id]] = cuisines[id]
            foodToRating[foods[id]] = ratings[id]
            val cuisineData = CuisineData(foods[id], ratings[id])
            cuisineLookup[cuisines[id]]?.let {
                it.add(cuisineData)
            } ?: run {
                val newSet = TreeSet { l: CuisineData, r: CuisineData ->
                    if (l.rating == r.rating) l.food.compareTo(r.food) else r.rating - l.rating
                }
                newSet.add(cuisineData)
                cuisineLookup[cuisines[id]] = newSet
            }
        }
    }
    
    fun changeRating(food: String, newRating: Int) {
        val cuisine = foodToCuisine[food]!!
        val oldKey = CuisineData(food, foodToRating[food]!!)
        val newKey = CuisineData(food, newRating)
        foodToRating[food] = newRating
        cuisineLookup[cuisine]?.let {
            it.remove(oldKey)
            it.add(newKey)
        }
    }

    fun highestRated(cuisine: String): String {
        return cuisineLookup[cuisine]!!.first().food
    }

}

/**
 * Your FoodRatings object will be instantiated and called as such:
 * var obj = FoodRatings(foods, cuisines, ratings)
 * obj.changeRating(food,newRating)
 * var param_2 = obj.highestRated(cuisine)
 */
 