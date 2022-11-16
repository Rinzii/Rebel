#pragma once

namespace rebel {
constexpr bool debug_v =
#if defined(REBEL_DEBUG)
	true;
#else
	false;
#endif
} // namespace rebel
