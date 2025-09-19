package template;
import java.io.*;
import java.util.*;

public class Template {
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() throws IOException {
            while (st == null || !st.hasMoreElements()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }

        int nextInt() throws IOException { return Integer.parseInt(next()); }
        long nextLong() throws IOException { return Long.parseLong(next()); }
        double nextDouble() throws IOException { return Double.parseDouble(next()); }
        String nextLine() throws IOException { return br.readLine(); }
    }

    public static void main(String[] args) throws IOException {
        FastReader fr = new FastReader();
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));

        int t = fr.nextInt();  // number of test cases
        while (t-- > 0) {
            int n = fr.nextInt();
            int[] arr = new int[n];
            for (int i = 0; i < n; i++) arr[i] = fr.nextInt();

            long sum = 0;
            for (int x : arr) sum += x;

            out.write(sum + "\n");
        }
        out.flush();
    }
}
