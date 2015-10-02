#include "cbdatasource.h"

#include "cbcookieget.h"
#include "cbcookieremove.h"
#include "cbqstringconvert.h"

#include <libcouchbase/couchbase.h>
#include <libcouchbase/views.h>
#include <libcouchbase/n1ql.h>
#include <stdio.h>

#include <QDebug>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QException>

static void
storage_callback(lcb_t instance, const void *cookie,
                 lcb_storage_t op, lcb_error_t err,
                 const lcb_store_resp_t *resp)
{
    if (err != LCB_SUCCESS)
    {
        qDebug() << QString("Couldn't store item to cluster: %1")
                    .arg(QString::fromUtf8(lcb_strerror(instance, err)));
}
}

static void
get_callback(lcb_t instance, const void *cookie, lcb_error_t err,
             const lcb_get_resp_t *resp)
{
    CBCookieGet* cbCookieGet = CBCookieGet::fromPointer(cookie);

    // HINT:
    //  - Use CBQStringConvert to get the key from the response
    //  - Convert the response into a CouchbaseDocument
    //  - add it to the cookie's item map
}

static void
removed_callback(lcb_t instance, const void *cookie, lcb_error_t err, const lcb_remove_resp_t *resp)
{
    CBCookieRemove* cbCookieRemove = CBCookieRemove::fromPointer(cookie);

    // HINT:
    //  - Test if the remove operation was successful
    //  - set the success value in the cookie
    //  - add some debug output using qDebug() << "Your Message"
    //  - use QString::fromUtf8(lcb_strerror(instance, err)) to convert the error into a QString
}

CBDataSource::CBDataSource()
    : mIsConnected(false)
{
}

void CBDataSource::Connect(const QString &connectionString)
{
    if (mIsConnected)
    {
        return;
    }

    CBQStringConvert connStrConv(connectionString);


    //TODO: Excercise 7a

    mIsConnected = true;
}

void CBDataSource::Destroy()
{
    if (mIsConnected && mInstance != NULL)
    {
        lcb_destroy(mInstance);
        mInstance = NULL;
    }
}

bool CBDataSource::Upsert(QString key, QString document)
{
    CBQStringConvert keyConv(key);
    CBQStringConvert docConv(document);

    //TODO: Exercise 8a

    return false;
}

bool CBDataSource::Upsert(QString key, QJsonObject document)
{
    QJsonDocument doc(document);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return Upsert(key, strJson);
}

bool CBDataSource::Delete(QString key)
{
    CBCookieRemove cookie;
    CBQStringConvert keyConv(key);

    //TODO: Exercise 10

    return false;
}


bool CBDataSource::IncrCounter(QString name, int delta, int initial)
{
    CBQStringConvert nameConv(name);

    lcb_arithmetic_cmd_t cmd;
    memset(&cmd, 0, sizeof cmd);
    const lcb_arithmetic_cmd_t *cmdlist = &cmd;
    cmd.v.v0.key = nameConv;
    cmd.v.v0.nkey = nameConv.length();
    cmd.v.v0.delta = delta; // Increment by
    cmd.v.v0.initial = initial; // Set to this if it does not exist
    cmd.v.v0.create = 1; // Create item if it does not exist
    lcb_error_t err = lcb_arithmetic(mInstance, NULL, 1, &cmdlist);
    return (err == LCB_SUCCESS);
}

CouchbaseDocument CBDataSource::Get(QString key)
{
    CBCookieGet cookie;
    CBQStringConvert keyConv(key);

    //TODO: Exercise 9a

    return cookie.items.first();
}

CouchbaseDocumentMap CBDataSource::MultiGet(QStringList keys)
{
    CBCookieGet cookie;

    //TODO: Exercise 11

    return cookie.items;
}

static void viewCallback(lcb_t instance, int ign, const lcb_RESPVIEWQUERY *rv)
{
    CBQueryResult* cookie = CBQueryResult::fromPointer(rv->cookie);

    // HINT:
    //  - test if the response is the final one
    //  - if so, extract the "total_rows"
    //      (convert the value field into a QJsonObject using CBQStringConvert) and
    //      store it to the cookie
    //  - if it is not the final response, extract docid and value using CBQStringConvert
    //  - store them into a CBQueryResultEntry
    //  - add it to the cookie's items
    //  - add some debug output using qDebug() << "Your Message"
}

CBQueryResult CBDataSource::QueryView(QString designDocName, QString viewName, int limit, int skip)
{
    CBQueryResult cookie;

    //TODO: Exercise 12

    return cookie;
}

static void n1qlCallback(lcb_t instance, int cbtype, const lcb_RESPN1QL *resp)
{
    CBN1qlResult* cbN1qlResult = CBN1qlResult::fromPointer(resp->cookie);

    // HINT:
    //  - test, if the response is the final one
    //  - if NOT, convert the row field into a QJsonObject using CBQStringConvert
    //  - store it to the cookie
}

CBN1qlResult CBDataSource::QueryN1ql(QString query)
{
    CBN1qlResult cookie;
    CBQStringConvert queryConv(query);

    //TODO: Exercise 13

    return cookie;

}

