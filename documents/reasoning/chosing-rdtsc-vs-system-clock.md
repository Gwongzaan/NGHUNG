
  characteristics
  - Hardwar-Level Access:

      rdtsc is a machine instruction that directly reads the processor's time stamp counter.
      This counter increments with each clock cycle of the CPU,

  - High Resolution:

      it provides very fine-grained timing, as it measures in CPU clock cycles

  - Platform specific:

      it is architecture-dependent (primarily x86/x64), it is not protable across different CPU architectures

  - Potential Issues:

      - Frequency Scaling can affect the accuracy
      - Out-of_order execution: Modern CPUs execute instructions out of order, which can make it challenging to obtain precise timings
      - Multi-Core/Multi-Processor: it multi-core systems, rdtsc values may differ between cores, requiring careful handling.

  Use Cases:
      - low-level performance analysis, micro-benchmarking, and situations where extremely precise timing is crucial and platform protability is not a concern



      - Standard Library Abstraction:

          std::chrono::high_resolution_clock is part of the C++ standard library, providing a portable way to measure time.

      - Implementation-Defined:

          The actual implementation of high_resolution_clock is implementation-defined. It might be an alias for std::chrono::system_clock, std::chrono::steady_clock, or a separate high-resolution clock provided by the system.

      - Portability:

          It offers better portability across different platforms compared to rdtsc.

      - Abstraction Overhead:

          There might be some overhead associated with the std::chrono library compared to the direct rdtsc instruction.

      - Varied Accuracy:

          The accuracy of high_resolution_clock can vary depending on the platform and its implementation.
          It's important to be aware that high_resolution_clock is not guaranteed to be a steady clock (meaning that the time between ticks is not guaranteed to be constant). For time interval measurement, std::chrono::steady_clock is generally preferred.

      Use Cases:

          General-purpose timing, benchmarking, and situations where portability and ease of use are important.