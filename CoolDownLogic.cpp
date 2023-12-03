#include <iostream>
#include <chrono>
#include <thread>

void yourFunction() {
    // Your function logic here
    std::cout << "Function called at: " << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << std::endl;
}

int main() {
    // Define the cooldown duration
    const std::chrono::milliseconds cooldownDuration(100);

    // Start time point
    auto startTime = std::chrono::steady_clock::now();

    while (true) {
        // Check if the cooldown period has passed
        auto currentTime = std::chrono::steady_clock::now();
        if (currentTime - startTime >= cooldownDuration) {
            // Call your function
            yourFunction();

            // Update the start time for the next cooldown period
            startTime = currentTime;
        }

        // Add a small delay to avoid busy waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
