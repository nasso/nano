/**
 * Trim whitespace at the beginning and end of every line in the template
 * literal and join lines.
 *
 * @param strings Template strings array
 * @param values Template literal values
 * @returns The processed string
 */
export function triml(
  strings: TemplateStringsArray,
  ...values: Array<number | string>
): string {
  return strings
    .reduce((text, str, i) => `${text}${str}${values[i] ?? ""}`, "")
    .split("\n")
    .map((line) => line.trim())
    .join("");
}

export function us(
  strings: TemplateStringsArray,
  ...values: Array<number | string>
): string {
  return strings
    .reduce((text, str, i) => `${text}${str}${values[i] ?? ""}`, "")
    .replace(/\s+/, "");
}

export interface Point {
  x: number;
  y: number;
}
