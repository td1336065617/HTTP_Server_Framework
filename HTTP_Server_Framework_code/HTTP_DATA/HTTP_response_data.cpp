//
// Created by fspst on 23-10-28.
//

#include "HTTP_response_data.h"

namespace Epoll_server {
    HTTP_response_data::~HTTP_response_data() {

    }

    int HTTP_response_data::set_http_response_value() {
        try{
            //以下组合响应头
            if (HTTP_Status_Code != "")
                http_response_value += HTTP_Status_Code + "\r\n";

            if (HTTP_Cache_Control != "")
                http_response_value += "Cache-Control:max-age=" + HTTP_Cache_Control + "\r\n";

            if (HTTP_Allow != "")
                http_response_value += "Allow:" + HTTP_Allow + "\r\n";

            if (HTTP_Connection != "")
                http_response_value += "Connection:" + HTTP_Connection + "\r\n";

            if (HTTP_Content_Encoding != "")
                http_response_value += "Content-Encoding:" + HTTP_Content_Encoding + "\r\n";

            if (HTTP_Content_Length != "")
                http_response_value += "Content-Length:" + HTTP_Content_Length + "\r\n";

            if (HTTP_Content_Type != "")
                http_response_value += "Content-Type:" + HTTP_Content_Type + "\r\n";

            if (HTTP_Date != "")
                http_response_value += "Date:" + HTTP_Date + "\r\n";

            if (HTTP_Expires != "")
                http_response_value += "Expires:" + HTTP_Expires + "\r\n";

            if (HTTP_Last_Modified != "")
                http_response_value += "Last-Modified:" + HTTP_Last_Modified + "\r\n";

            if (HTTP_Refresh != "")
                http_response_value += "Refresh:" + HTTP_Refresh + "\r\n";

            if (HTTP_Server != "")
                http_response_value += "Server:" + HTTP_Server + "\r\n";

            if (HTTP_Set_Cookie != "")
                http_response_value += "Set-Cookie:" + HTTP_Set_Cookie + "\r\n";

            if (HTTP_WWW_Authenticate != "")
                http_response_value += "WWW-Authenticate:" + HTTP_WWW_Authenticate + "\r\n";
            if (Location!="")
            {
                http_response_value+="Location:" + Location + "\r\n";
            }
            if (custom_response_value != "")
                http_response_value += custom_response_value+ "\r\n";
            //cout<<http_response_value<<"\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return 0;
    }

    HTTP_response_data::HTTP_response_data(){
        
    }

    std::ostream &operator<<(std::ostream &os, const HTTP_response_data &data) {
        os << "value: " << data.value << " response_ip: " << data.response_ip << " response_post: "
           << data.response_post << " acceptbj: " << data.acceptbj << " HTTP_Content_Length_size: "
           << data.HTTP_Content_Length_size << " Resource_path: " << data.Resource_path << " HTTP_Status_Code: "
           << data.HTTP_Status_Code << " HTTP_Cache_Control: " << data.HTTP_Cache_Control << " HTTP_Allow: "
           << data.HTTP_Allow << " HTTP_Content_Encoding: " << data.HTTP_Content_Encoding << " HTTP_Content_Length: "
           << data.HTTP_Content_Length << " HTTP_Content_Type: " << data.HTTP_Content_Type << " HTTP_Date: "
           << data.HTTP_Date << " HTTP_Expires: " << data.HTTP_Expires << " HTTP_Last_Modified: "
           << data.HTTP_Last_Modified << " HTTP_Location: " << data.HTTP_Location << " HTTP_Refresh: "
           << data.HTTP_Refresh << " HTTP_Server: " << data.HTTP_Server << " HTTP_Set_Cookie: " << data.HTTP_Set_Cookie
           << " HTTP_WWW_Authenticate: " << data.HTTP_WWW_Authenticate << " HTTP_Connection: " << data.HTTP_Connection
           << " host: " << data.host << " HTTP_Cookie: " << data.HTTP_Cookie << " custom_response_value: "
           << data.custom_response_value << " http_response_value: " << data.http_response_value
           << " http_response_data_value: " << data.http_response_data_value;
        return os;
    }

 
} // Epoll_server