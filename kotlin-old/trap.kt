import kotlin.math.*
import kotlinx.coroutines.experimental.*

fun integral(f: (Double) -> Double, range: List<Double>, n: Int) : Double {

    // destructure range into a and b
    val (a, b) = range

    val dx = (a - b) / 2

    println(dx)


    val c = AtomicInteger()

    for (i in 1..1_000_000)
        launch {
            c.addAndGet(i)
        }

    println(c.get())

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