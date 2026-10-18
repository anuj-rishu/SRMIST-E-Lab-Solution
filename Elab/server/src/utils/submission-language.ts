export type SubmissionLanguage = "c" | "cpp";

export function submissionLanguage(source: string): SubmissionLanguage {
  // Preserve literals while removing comments, so commented examples don't
  // switch a C solution to C++ and comment markers inside strings stay intact.
  const uncommented = source.replace(
    /"(?:\\[\s\S]|[^"\\])*"|'(?:\\[\s\S]|[^'\\])*'|\/\*[\s\S]*?\*\/|\/\/[^\r\n]*/g,
    (token) => (token.startsWith("/") ? " " : token),
  );
  const cppHeader =
    /^\s*#\s*include\s*[<"](?:bits\/[^>"]+|(?:iostream|istream|ostream|ios|iosfwd|iomanip|fstream|sstream|streambuf|vector|array|deque|list|forward_list|stack|queue|map|set|unordered_map|unordered_set|string|string_view|algorithm|numeric|bitset|tuple|utility|functional|iterator|memory|limits|new|exception|stdexcept|type_traits|optional|variant|any|chrono|random|complex|valarray|regex|thread|mutex|atomic|condition_variable|filesystem|cassert|cctype|cerrno|cfloat|cinttypes|climits|clocale|cmath|cstddef|cstdint|cstdio|cstdlib|cstring|ctime|cwchar|cwctype))[>"]/m;
  if (cppHeader.test(uncommented)) return "cpp";
  const code = uncommented.replace(
    /"(?:\\[\s\S]|[^"\\])*"|'(?:\\[\s\S]|[^'\\])*'/g,
    " ",
  );
  return /\bstd\s*::|\busing\s+namespace\b|\b(?:cin|cerr|clog)\s*>>|\b(?:cout|cerr|clog)\s*<<|\b(?:vector|priority_queue|unordered_map|unordered_set|map|set|stack|queue|bitset)\s*<|\b(?:template\s*<|namespace\s+\w+|class\s+\w+|constexpr\b|nullptr\b)/.test(
    code,
  )
    ? "cpp"
    : "c";
}
