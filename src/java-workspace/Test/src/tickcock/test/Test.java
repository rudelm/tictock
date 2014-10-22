package tickcock.test;

import java.util.ArrayList;
import java.util.List;

import org.joda.time.DateTime;

enum Word {
	WORT_ES(0, "Es"), WORT_IST(3, "ist"), MINUTE_FÜNF(7, "fünf"), MINUTE_ZEHN(
			11, "zehn"), MINUTE_FÜNFZEHN(7, "fünfzehn"), MINUTE_ZWANZIG(15,
			"zwanzig"), MINUTE_DREIVIERTEL(22, "dreiviertel"), MINUTE_VIERTEL(
			26, "viertel"), WORT_NACH(35, "nach"), WORT_VOR(39, "vor"), MINUTE_HALB(
			44, "halb"), STUNDE_ZWÖLF(49, "zwölf"), STUNDE_ZWEI(55, "zwei"), STUNDE_EIN(
			57, "ein"), STUNDE_EINS(57, "eins"), STUNDE_SIEBEN(60, "sieben"), STUNDE_DREI(
			67, "drei"), STUNDE_FÜNF(73, "fünf"), STUNDE_ELF(77, "elf"), STUNDE_NEUN(
			80, "neun"), STUNDE_VIER(84, "vier"), STUNDE_ACHT(89, "acht"), STUNDE_ZEHN(
			93, "zehn"), STUNDE_SECHS(100, "sechs"), WORT_UHR(107, "Uhr");

	// ---------------------------------- 1
	// ---------------------------------- 1 2 3 4 5 6 7 8 9 0
	// ----------------------------------01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
	public static final char[] MATRIX = "eskistlfünfzehnzwanzigdreivierteltgnachvorjmhalbqzwölfpzweinsiebenkdreirhfünfelfneunvierwachtzehnrsbsechssfuhr"
			.toCharArray();

	private int start;

	private char[] text;

	private Word(int start, String text) {
		this.start = start;
		this.text = text.toCharArray();
	}

	public int getStart() {
		return start;
	}

	public int getLength() {
		return text.length;
	}

	public char[] getText() {
		return text;
	}
}

public class Test {
	private static final Word[] MINUTE_WORDS = { null, Word.MINUTE_FÜNF,
			Word.MINUTE_ZEHN, Word.MINUTE_VIERTEL, Word.MINUTE_ZWANZIG,
			Word.MINUTE_FÜNF, Word.MINUTE_HALB, Word.MINUTE_FÜNF,
			Word.MINUTE_ZWANZIG, Word.MINUTE_VIERTEL, Word.MINUTE_ZEHN,
			Word.MINUTE_FÜNF };

	private static final Word[] CONNECTOR_WORDS = { null, Word.WORT_NACH,
			Word.WORT_NACH, Word.WORT_NACH, Word.WORT_NACH, Word.WORT_VOR,
			null, Word.WORT_NACH, Word.WORT_VOR, Word.WORT_VOR, Word.WORT_VOR,
			Word.WORT_VOR };

	private static final Word[] HOUR_WORDS = { Word.STUNDE_ZWÖLF,
			Word.STUNDE_EINS, Word.STUNDE_ZWEI, Word.STUNDE_DREI,
			Word.STUNDE_VIER, Word.STUNDE_FÜNF, Word.STUNDE_SECHS,
			Word.STUNDE_SIEBEN, Word.STUNDE_ACHT, Word.STUNDE_NEUN,
			Word.STUNDE_ZEHN, Word.STUNDE_ELF };

	private static final String[] MINUTE_INDICATORS = { "", "+", "++", "--",
			"-" };

	public static List<Word> words(int minutesOfDay) {
		int hours = (minutesOfDay + 2) / 60;
		int minutes = (minutesOfDay + 2) % 60;
		int minuteIndex = minutes / 5;
		int hourIndex = hours % 12;

		List<Word> words = new ArrayList<>();

		words.add(Word.WORT_ES);
		words.add(Word.WORT_IST);

		words.add(MINUTE_WORDS[minuteIndex]);
		words.add(CONNECTOR_WORDS[minuteIndex]);

		if (minuteIndex == 5 || minuteIndex == 7)
			words.add(Word.MINUTE_HALB);

		if (minuteIndex == 0 && hourIndex == 1)
			words.add(Word.STUNDE_EIN);
		else {
			if (minuteIndex > 4)
				hourIndex = (hourIndex + 1) % 12;
			words.add(HOUR_WORDS[hourIndex]);
		}

		if (minuteIndex == 0)
			words.add(Word.WORT_UHR);

		return words;
	}

	public static String wordTime(int minutesOfDay) {
		int minutePoints = minutesOfDay % 5;

		List<Word> words = words(minutesOfDay);
		StringBuilder sb = new StringBuilder();
		for (Word word : words) {
			if (word != null) {
				sb.append(word.getText());
				sb.append(" ");
			}
		}
		sb.append(MINUTE_INDICATORS[minutePoints]);

		return sb.toString().trim();
	}

	public static String wordTime2(int minuteOfDay) {
		int minutePoints = minuteOfDay % 5;

		List<Word> words = words(minuteOfDay);
		char[] result = new char[Word.MATRIX.length];
		System.arraycopy(Word.MATRIX, 0, result, 0, result.length);
		for (Word word : words) {
			if (word != null) {
				for (int i = 0; i < word.getLength(); i++) {
					int idx = word.getStart() + i;
					result[idx] = Character.toUpperCase(result[idx]);
				}
			}
		}
		return new String(result);
	}

	public static void main(String[] args) {
		System.out.println(wordTime(DateTime.now().getMinuteOfDay()));
		System.out.println(wordTime2(DateTime.now().getMinuteOfDay()));
	}
}