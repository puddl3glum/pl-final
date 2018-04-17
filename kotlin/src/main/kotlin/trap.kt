import kotlin.math.*
import kotlinx.coroutines.experimental.*

fun integral(f: (Double) -> Double, range: List<Double>, n: Int) : Double {

    // destructure range into a and b
    val (a, b) = range

    val dx = (a - b) / 2

    println(dx)


    val deferred = (1..1_000_000).map { n ->
        async {
            n
        }
    }

    runBlocking {
        val sum = deferred.sumBy { it.await() }
        println("Sum: $sum")
    }

    return 2.0
}

fun main(args : Array<String>) {

    val a = args[0].toDouble()
    val b = args[1].toDouble()

    println(a)
    println(b)

    val f = {x: Double -> exp(3 * x) * sin(2 * x)}

    val range = listOf(a, b)

    val integral_val = integral(f, range, 1000)

    println(integral_val)
}