这是一个基于EPOLL+socket+线程池模式的一个C++ HTTP库，目前仅支持POST/GET两种模式。
如果下使用这个库 你只需要导入lib目录下的libHTTP_Server_Framework.so动态链接库，和include下的头文件。
你需要继承    HTTP_Server_Framework类 并重写其的
virtual int Task_distribution_center(HTTP_request_data httpRequestData, HTTP_response_data &httpResponseData);//如果需要对HTTP请求的数据进行处理，继承后重写任务分配中心
通过httpRequestData你可以得到前端的请求信息，包括所有请求头，分割过的post JSON/ GET 链接尾部附加的数据。
你只需要将你想响应的数据修改入httpResponseData，库会选择较快的那种方式进行响应（具体可见下方的模板）。

```C++
 class HTTP_request_data {
    public:
        int acceptbj = 0;                              //请求的套接子的描述符
        string url = "";                               //请求的文件的本地url
        string Location="";
        string Type = "";                              //请求的文件的类型
        string Request_type = "";                      //请求类型
        string HTTP_Cookie = "";                       //Cookie
        string Request_http_type = "";                 //请求头的http类型
        unordered_map<string, string> http_value;      //请求头分割后存在这里
        unordered_map<string, string> http_data_value; //分解后的post or get数据都在里面
        unordered_map<string, string> HTTP_Cookie_value;//分解后的cooike;
        string HTTP_If_Modified_Since;                 //服务器缓存文件的最后修改时间

    void set_requst_initialize();
        string POST_Json_Data();
    };
```

```C++
class HTTP_response_data {
    public:
        string Location;
        int file_or_data=0;//如果要返回的是文件 0 如果是数据1
        bool value;                                    //是否存在数据
        string response_ip;                            //是否需要将数据POST去另外地址
        string response_post;                          //
        int acceptbj = 0;                              //请求的套接子 的描述符
        off_t HTTP_Content_Length_size;                //文件大小
        string testtype="";                            //返回的是文件的话 文件类型
        string HTTP_If_Modified_Since;                 //服务器缓存文件的最后修改时间
        string Resource_path = "";                     //返回的文件的地址 服务器会自动合成请求路径默认为返回文件 如果不想返回文件请在取得http_response后设置为字符串 "" 一个非null但空白的字符串
        string HTTP_Status_Code = "";                  //服务器响应状态
        string HTTP_Cache_Control = "";                //设置浏览器缓存机制
        string HTTP_Allow = "";                        //服务器支持哪些请求方法（如GET、POST等）。
        string HTTP_Content_Encoding = "";             //文档的编码（Encode）方法。只有在解码之后才可以得到Content-Type头指定的内容类型。利用gzip压缩文档能够显著地减少HTML文档的下载时间。Java的GZIPOutputStream可以很方便地进行gzip压缩，但只有Unix上的Netscape和Windows上的IE 4、IE 5才支持它。因此，Servlet应该通过查看Accept-Encoding头（即request.getHeader("Accept-Encoding")）检查浏览器是否支持gzip，为支持gzip的浏览器返回经gzip压缩的HTML页面，为其他浏览器返回普通页面。
        string HTTP_Content_Length = "";               //表示内容长度。
        string HTTP_Content_Type = "";                 //表示后面的文档属于什么MIME类型。Servlet默认为text/plain，但通常需要显式地指定为text/html。由于经常要设置Content-Type，因此HttpServletResponse提供了一个专用的方法setContentType。
        string HTTP_Date = "";                         //当前的GMT时间。你可以用setDateHeader来设置这个头以避免转换时间格式的麻烦。
        string HTTP_Expires;                           //应该在什么时候认为文档已经过期，从而不再缓存它？
        string HTTP_Last_Modified = "";                //文档的最后改动时间。客户可以通过If-Modified-Since请求头提供一个日期，该请求将被视为一个条件GET，只有改动时间迟于指定时间的文档才会返回，否则返回一个304（Not Modified）状态。Last-Modified也可用setDateHeader方法来设置。
        string HTTP_Location = "";                     //表示客户应当到哪里去提取文档。Location通常不是直接设置的，而是通过HttpServletResponse的sendRedirect方法，该方法同时设置状态代码为302。
        string HTTP_Refresh = "";                      //表示浏览器应该在多少时间之后刷新文档以秒计。
        string HTTP_Server = "";                       //服务器名字。
        string HTTP_Set_Cookie = "";                   //设置和页面关联的Cookie。
        string HTTP_WWW_Authenticate = "";             //客户应该在Authorization头中提供什么类型的授权信息？在包含401（Unauthorized）状态行的应答中这个头是必需的。例如，response.setHeader("WWW-Authenticate", "BASIC realm=＼"executives＼"")。
        string HTTP_Connection = "";                   //是否使用长链接
        string host = "";                              //调试用
        string HTTP_Cookie = "";                       //请求头内包含的Cookie
        string custom_response_value="";               //自定义的响应填充到这里 服务器会在响应头末尾加上
        string http_response_value = "";               //以上信息会自动组成响应头存在这里
        string http_response_data_value="";            //非文件形数据存进这里然后服务器自动发送
        unordered_map<string, string> http_data_value; //分解后的post or get数据都在里
        unordered_map<string, string> HTTP_Cookie_value;//分解后的cooike;
        unordered_map<string, string> http_value;      //请求头分割后存在这里
        HTTP_response_data();
        virtual ~HTTP_response_data();
        int set_http_response_value();//数据返回之前进行组合
        friend std::ostream &operator<<(std::ostream &os, const HTTP_response_data &data);
    };
```


