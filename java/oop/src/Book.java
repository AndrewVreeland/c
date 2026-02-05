public class Book {

    String author;
    boolean coverType;
    int pages = 400;
    int year = 2027;

    public Book(String givenAuthorName, boolean givenCoverType) {
        author = givenAuthorName;
        coverType = givenCoverType;
        pages = 300;
        year = 1910;

    }
    public Book( boolean givenCoverType) {
        coverType = givenCoverType;
        pages = 500;
        year = 1910;

    }

    public void getRead()
    {
        System.out.println(pages + " are read");
    }
}
