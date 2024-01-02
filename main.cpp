#include "GameManager.hh"

#include <iostream>
#include <memory>

// TRACK MEMORY ALLOCATIONS (for testing)
// ---------------------------------------------------------------------------------------
struct AllocationMetrics
{
  uint32_t totalMemoryAllocated = 0;
  uint32_t totalMemoryFreed = 0;

  uint32_t CurrentMemoryUsage() { return totalMemoryAllocated - totalMemoryFreed; }
};

static AllocationMetrics allocationMetrics;

void *operator new(size_t size)
{
  allocationMetrics.totalMemoryAllocated += size;

  return malloc(size);
}

void operator delete(void *memory, size_t size) noexcept
{
  allocationMetrics.totalMemoryFreed += size;

  free(memory);
}

static void PrintMemoryUsage()
{
  printf("Memory usage: %u bytes\n", allocationMetrics.CurrentMemoryUsage());
}
// ---------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  PrintMemoryUsage();
  try
  {
    std::unique_ptr<GameManager> gm = std::make_unique<GameManager>();

    gm->StartGame();
    gm->GameLoop();
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << '\n';
  }
  catch (...)
  {
    printf("Some error occurred. \n");
  }

  return 0;
}
