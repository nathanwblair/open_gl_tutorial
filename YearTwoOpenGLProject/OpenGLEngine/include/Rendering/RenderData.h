#pragma once

#include <Utils.h>

class RenderData
{
private:
    uint vao;
    uint vbo;
    uint ibo;

    uint uiIndexCount;

    void PipePositive(uchar& output, uint positive, uchar pipeValue)
    {
        if (positive > 0)
            output |= pipeValue;
    }

public:
    RenderData()
        : vao(0),
        vbo(0),
        ibo(0),
		uiIndexCount(0)
    {
    }

    ~RenderData()
    {
        DestroyBuffers(Buffers::ALL);
    }

    RenderData(const RenderData& other)
    {
        vao = other.vao;
        vbo = other.vbo;
        ibo = other.ibo;
    }

    RenderData(RenderData&& other)
    {
        vao = other.vao;
        vbo = other.vbo;
        ibo = other.ibo;

        other.Clear();
    }

    enum Buffers : uchar
    {
        VAO = 1,
        VBO = 2,
        IBO = 4,
        ALL = 7
    };

	void SetIndexCount(uint count)
	{
		uiIndexCount = count;
	}

    void GenerateBuffers(uchar uiBuffers)
    {
        DestroyBuffers(uiBuffers);

        if (uiBuffers & Buffers::VAO)
        {
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
        }

        if (uiBuffers & Buffers::VBO)
        {
            glGenBuffers(1, &vbo);
            if (uiBuffers & Buffers::VAO)
            {
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
            }
        }

        if (uiBuffers & Buffers::IBO)
        {
            glGenBuffers(1, &ibo);
            if (uiBuffers & Buffers::IBO)
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        }

        if (uiBuffers & Buffers::VAO)
            glBindVertexArray(0);
    }

    void DestroyBuffers(uchar uiBuffers)
    {
        if (uiBuffers & Buffers::VAO && vao > 0)
        {
            glDeleteVertexArrays(1, &vao);
        }

        if (uiBuffers & Buffers::VAO && vbo > 0)
        {
            glDeleteBuffers(1, &vbo);
        }

        if (uiBuffers & Buffers::IBO && ibo > 0)
        {
            glDeleteBuffers(1, &ibo);
        }

    }

    uint GetVAO() const
    {
        return vao;
    }

    uint GetVBO() const
    {
        return vbo;
    }

    uint GetIBO() const
    {
        return ibo;
    }

    void CheckBuffers(uchar& uiBuffers)
    {
        uiBuffers = 0;

        PipePositive(uiBuffers, vao, Buffers::VAO);
        PipePositive(uiBuffers, vbo, Buffers::VBO);
        PipePositive(uiBuffers, ibo, Buffers::IBO);
    }

    void Bind()
    {
        if (vao >  0)
        {
            glBindVertexArray(vao);
        }
        else if (vbo > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            if (ibo > 0)
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        }
    }

    void Render()
    {
        if (ibo)
        {
            glDrawElements(GL_TRIANGLES, uiIndexCount, GL_UNSIGNED_INT, 0);
        }
    }

    void Clear()
    {
        vao = 0;
        vbo = 0;
        ibo = 0;
    }

    void Unbind()
    {
        if (vao > 0)
        {
            glBindVertexArray(0);
        }
        else if (vbo > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            if (ibo > 0)
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
        }
    }
};